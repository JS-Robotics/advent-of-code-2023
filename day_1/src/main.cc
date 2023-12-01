///
/// Created by JS-Robotics on 01.12.23.
///


#include <iostream>
#include <fstream>

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

void ReadAndPrintLines(std::ifstream &file) {
  std::string line;
  while (std::getline(file, line)) {
    std::cout << line << std::endl;
  }
}

int main() {
  std::cout << "Hello AoC Day 1! \n" << std::endl;

  const char *file_name = "../data/day_1_example.txt";
  std::ifstream file = OpenFile(file_name);
  ReadAndPrintLines(file);
  CloseFile(file);
  return 0;

}