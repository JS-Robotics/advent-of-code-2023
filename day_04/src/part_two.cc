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

  int sum = 0;
  std::string line;

  while (std::getline(file, line)) {
    std::cout << line << std::endl;

  }

  return sum;
}

int main() {
  std::cout << "Hello AoC Day 4! \n" << std::endl;


  /*!
   * Solving plan
   * Keep track of symbol index, check if diagonal or next to strings
   * in line, over and above.
   */

  const char *file_name = "../data/day_04_example.txt";
  std::ifstream file = OpenFile(file_name);
  int calibration_sum = ReadAndProcessGames(file);
  std::cout << "The engine schematic sum is: \033[32m" << calibration_sum << "\033[0m" << std::endl;
  CloseFile(file);
  return 0;

}