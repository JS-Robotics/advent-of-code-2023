///
/// Created by JS-Robotics on 01.12.23.
///


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>

std::ifstream OpenFile(const std::string &file_name) {
  std::ifstream file(file_name);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << file_name << std::endl;
    exit(1);
  }
  return file;
}

void CloseFile(std::ifstream &file) {
  file.close();
}

int GetGameID(const std::string &line, const std::regex &pattern) {
  std::sregex_iterator iter(line.begin(), line.end(), pattern);
  std::sregex_iterator end;
  int value = 0;
  while (iter != end) {
    std::smatch match = *iter;
    value = std::stoi(match[1].str());
    ++iter;
  }
  return value;
}

bool CheckGameSetColors(const std::string &game_set) {
  std::regex pattern(R"((\d+)\s+(\w+))");
  std::sregex_iterator iter(game_set.begin(), game_set.end(), pattern);
  std::sregex_iterator end;

  int red_limit = 12;
  int green_limit = 13;
  int blue_limit = 14;

  bool game_is_valid = true;
  while (iter != end) {
    std::smatch match = *iter;
    int count = std::stoi(match[1].str());
    std::string color = match[2].str();

    if (color == "red") {
      game_is_valid &= count <= red_limit;
    }

    if (color == "green") {
      game_is_valid &= count <= green_limit;
    }

    if (color == "blue") {
      game_is_valid &= count <= blue_limit;
    }

    ++iter;
  }

  return game_is_valid;
}

bool GetValidGameData(const std::string &line, const std::regex &pattern) {
  std::sregex_iterator iter(line.begin(), line.end(), pattern);
  std::sregex_iterator end;

  bool game_is_valid = true;
  while (iter != end) {
    std::smatch match = *iter;
    game_is_valid &= CheckGameSetColors(match[1].str());
    ++iter;
  }

  return game_is_valid;
}

int ProcessGame(const std::string &line) {
  std::regex game_id_pattern("Game (\\d+):([^;]+)");  // Get the id of the game
  int game_id = GetGameID(line, game_id_pattern);

  std::regex game_data_pattern("([^:;]+)(?:;|$)");  // Match for every game set
  bool game_data_valid = GetValidGameData(line, game_data_pattern);

  if (game_data_valid) {
    return game_id;
  }

  return 0;
}

int ReadAndProcessGames(std::ifstream &file) {
  std::string game_line;
  int sum = 0;

  while (std::getline(file, game_line)) {
    sum += ProcessGame(game_line);
  }

  return sum;
}

int main() {
  std::cout << "Hello AoC Day 2! \n" << std::endl;

  const char *file_name = "../data/day_02_input.txt";
  std::ifstream file = OpenFile(file_name);
  int calibration_sum = ReadAndProcessGames(file);
  std::cout << "The sum of valid game IDs are: \033[32m" << calibration_sum << "\033[0m" << std::endl;
  CloseFile(file);
  return 0;

}