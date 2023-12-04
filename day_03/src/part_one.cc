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

int ReadAndProcessGames(std::ifstream &file) {
  std::string line;
  int sum = 0;
  std::vector<std::string> input;
  std::vector<std::string> string_set;
  std::string empty_line = "..........";
  string_set.reserve(3);
  int index = 0;
  while (std::getline(file, line)) {
    std::cout << line << std::endl;
    input.emplace_back(line);
  }

  for (int i = 1; i < (input.size() - 1); i++) {
    string_set[0] = input.at(i - 1);
    string_set[1] = input.at(i);
    string_set[2] = input.at(i + 1);

    std::cout << std::endl;
    std::cout << string_set[0] << std::endl;
    std::cout << string_set[1] << std::endl;
    std::cout << string_set[2] << std::endl;
    std::cout << std::endl;
  }

  return sum;
}

int main() {
  std::cout << "Hello AoC Day 3! \n" << std::endl;


  /*!
   * Solving plan
   * Keep track of symbol index, check if diagonal or next to strings
   * in line, over and above.
   */

  const char *file_name = "../data/day_03_example.txt";
  std::ifstream file = OpenFile(file_name);
  int calibration_sum = ReadAndProcessGames(file);
  std::cout << "The engine schematic sum is: \033[32m" << calibration_sum << "\033[0m" << std::endl;
  CloseFile(file);
  return 0;

}