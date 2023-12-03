///
/// Created by JS-Robotics on 01.12.23.
///


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>

struct ColorCount {
  int red_required = 0;
  int green_required = 0;
  int blue_required = 0;
};

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

ColorCount CheckGameSetColors(const std::string &game_set) {
  std::regex pattern(R"((\d+)\s+(\w+))");
  std::sregex_iterator iter(game_set.begin(), game_set.end(), pattern);
  std::sregex_iterator end;

  ColorCount color_count{};
  while (iter != end) {
    std::smatch match = *iter;
    int count = std::stoi(match[1].str());
    std::string color = match[2].str();

    if (color == "red") {
      color_count.red_required = count;
    }

    if (color == "green") {
      color_count.green_required = count;
    }

    if (color == "blue") {
      color_count.blue_required = count;
    }

    ++iter;
  }

  return color_count;
}

ColorCount CheckForHigherCount(ColorCount color_count_old, ColorCount color_count_new) {
  ColorCount color_count;

  if (color_count_new.red_required > color_count_old.red_required) {
    color_count.red_required = color_count_new.red_required;
  } else {
    color_count.red_required = color_count_old.red_required;
  }

  if (color_count_new.blue_required > color_count_old.blue_required) {
    color_count.blue_required = color_count_new.blue_required;
  } else {
    color_count.blue_required = color_count_old.blue_required;
  }

  if (color_count_new.green_required > color_count_old.green_required) {
    color_count.green_required = color_count_new.green_required;
  } else {
    color_count.green_required = color_count_old.green_required;
  }

  return color_count;

};

int GetValidGameDataPower(const std::string &line, const std::regex &pattern) {
  std::sregex_iterator iter(line.begin(), line.end(), pattern);
  std::sregex_iterator end;

  ColorCount current_color_count;
  while (iter != end) {
    std::smatch match = *iter;
    ColorCount new_color_count = CheckGameSetColors(match[1].str());
    current_color_count = CheckForHigherCount(current_color_count, new_color_count);
    ++iter;
  }

  int power = current_color_count.red_required * current_color_count.blue_required * current_color_count.green_required;
  return power;
}

int ProcessGame(const std::string &line) {
  std::regex game_data_pattern("([^:;]+)(?:;|$)");  // Match for every game set
  int power = GetValidGameDataPower(line, game_data_pattern);

  return power;
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
  std::cout << "The cube power sum is: \033[32m" << calibration_sum << "\033[0m" << std::endl;
  CloseFile(file);
  return 0;

}