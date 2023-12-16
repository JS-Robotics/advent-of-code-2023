///
/// Created by JS-Robotics on 16.12.23.
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

int ReadAndProcess(std::ifstream &file) {

  int sum = 0;
  std::string line;

  while (std::getline(file, line)) {

  }

  return sum;
}

int main() {
  std::cout << "Hello AoC Day 4! \n" << std::endl;

  const char *file_name = "../data/day_04_input.txt";
  std::ifstream file = OpenFile(file_name);
  int calibration_sum = ReadAndProcess(file);
  std::cout << "The cards total sum is: \033[32m" << calibration_sum << "\033[0m" << std::endl;
  CloseFile(file);
  return 0;

}