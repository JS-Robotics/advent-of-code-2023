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

bool CharIsNumber(char c) {
  if (c == '1') {
    return true;
  }
  if (c == '2') {
    return true;
  }
  if (c == '3') {
    return true;
  }
  if (c == '4') {
    return true;
  }
  if (c == '5') {
    return true;
  }
  if (c == '6') {
    return true;
  }
  if (c == '7') {
    return true;
  }
  if (c == '8') {
    return true;
  }
  if (c == '9') {
    return true;
  }
  return false;
}

std::vector<char> SearchLeft(const std::string &line, int idx) {
  std::vector<char> chars;
  for (int i = idx - 1; i > 0; i--) {
    if (CharIsNumber(line.at(i))) {
      chars.emplace_back(line.at(i));
    } else {
      break;
    }
  }
  return chars;
}

std::vector<char> SearchRight(const std::string &line, int idx) {
  std::vector<char> chars;
  for (int i = idx + 1; i < line.size() - 1; i++) {
    if (CharIsNumber(line.at(i))) {
      chars.emplace_back(line.at(i));
    } else {
      break;
    }
  }
  return chars;
}




int ReadAndProcessGames(std::ifstream &file) {
  std::string line;
  int sum = 0;
  std::vector<std::string> input;
  std::vector<std::string> string_set(3);
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

    int idx = 0;
    for (char c : string_set.at(1)) {
      if (c != '.' && !CharIsNumber(c)) {
//        std::cout << "Char is: " << c << std::endl;
        std::string number;
        if (CharIsNumber(string_set.at(0).at(idx))) {
          std::vector<char> chars = SearchLeft(string_set.at(0), idx);
          // Reverse loop using a range-based for loop and reverse iterators
          for (auto it = chars.rbegin(); it != chars.rend(); ++it) {
            char k = *it;
            number += k;
          }
          number += string_set.at(0).at(idx);
          chars = SearchRight(string_set.at(0), idx);
          for (char k : chars){
            number += k;
          }
        std::cout << "At sign: " << c << " - " << number << std::endl;
        }
      }
      idx++;
    }

//    std::cout << std::endl;
//    std::cout << string_set[0] << std::endl;
//    std::cout << string_set[1] << std::endl;
//    std::cout << string_set[2] << std::endl;
//    std::cout << std::endl;
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