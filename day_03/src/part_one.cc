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
  if (c == '0') {
    return true;
  }
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
  for (int i = idx + 1; i < line.size(); i++) {
    if (CharIsNumber(line.at(i))) {
      chars.emplace_back(line.at(i));
    } else {
      break;
    }
  }
  return chars;
}

int SearchLeftVal(const std::string &line, int idx) {
  std::vector<char> chars;
  for (int i = idx - 1; i >= 0; i--) {
    if (CharIsNumber(line.at(i))) {
      chars.emplace_back(line.at(i));
    } else {
      break;
    }
  }

  std::string number;
  for (auto it = chars.rbegin(); it != chars.rend(); ++it) {
    char k = *it;
    number += k;
  }

  if (number.empty()) {
    return 0;
  }

  return std::stoi(number);
}

int SearchRightVal(const std::string &line, int idx) {
  std::vector<char> chars;
  for (int i = idx + 1; i < line.size(); i++) {
    if (CharIsNumber(line.at(i))) {
      chars.emplace_back(line.at(i));
    } else {
      break;
    }
  }

  std::string number{};
  chars = SearchRight(line, idx);
  for (char k : chars) {
    number += k;
  }

  if (number.empty()) {
    return 0;
  }

  return std::stoi(number);
}

int SearchDiagLeft(const std::string &line, int idx) {
  std::vector<char> chars;
  for (int i = idx; i >= 0; i--) {
    if (CharIsNumber(line.at(i))) {
      chars.emplace_back(line.at(i));
    } else {
      break;
    }
  }

  std::string number;
  for (auto it = chars.rbegin(); it != chars.rend(); ++it) {
    char k = *it;
    number += k;
  }

  if (number.empty()) {
    return 0;
  }

  return std::stoi(number);
}

int SearchDiagRight(const std::string &line, int idx) {
  std::vector<char> chars;
  for (int i = idx; i < line.size(); i++) {
    if (CharIsNumber(line.at(i))) {
      chars.emplace_back(line.at(i));
    } else {
      break;
    }
  }

  std::string number{};
  chars = SearchRight(line, idx);
  for (char k : chars) {
    number += k;
  }

  if (number.empty()) {
    return 0;
  }

  return std::stoi(number);
}

int SearchTop(const std::string &line, int idx, char c) {
  int num = 0;
  std::string number;
  if (CharIsNumber(line.at(idx))) {
    std::vector<char> chars = SearchLeft(line, idx);

    // Reverse loop using a range-based for loop and reverse iterators
    for (auto it = chars.rbegin(); it != chars.rend(); ++it) {
      char k = *it;
      number += k;
    }
    number += line.at(idx);
    chars = SearchRight(line, idx);
    for (char k : chars) {
      number += k;
    }
//    std::cout << "At sign: " << c << " - " << number << std::endl;
    num = std::stoi(number);
  }
  return num;
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
        int sum_part = 0;
        sum_part = SearchTop(string_set.at(0), idx, c);
        sum += sum_part;
        if (sum_part != 0) {
          std::cout << "At sign: " << c << " - " << sum_part << std::endl;
        } else if (sum_part == 0) {
          sum_part = SearchDiagLeft(string_set.at(0), idx - 1);
          sum += sum_part;
          if (sum_part != 0) {
            std::cout << "At sign: " << c << " - " << sum_part << std::endl;
          }

          sum_part = SearchDiagRight(string_set.at(0), idx);
          sum += sum_part;
          if (sum_part != 0) {
            std::cout << "At sign: " << c << " - " << sum_part << std::endl;
          }
        }

        sum_part = SearchTop(string_set.at(2), idx, c);
        sum += sum_part;
        if (sum_part != 0) {
          std::cout << "At sign: " << c << " - " << sum_part << std::endl;
        } else if (sum_part == 0) {
          sum_part = SearchDiagLeft(string_set.at(2), idx - 1);
          sum += sum_part;
          if (sum_part != 0) {
            std::cout << "At sign: " << c << " - " << sum_part << std::endl;
          }

          sum_part = SearchDiagRight(string_set.at(2), idx);
          sum += sum_part;
          if (sum_part != 0) {
            std::cout << "At sign: " << c << " - " << sum_part << std::endl;
          }
        }

        sum_part = SearchRightVal(string_set.at(1), idx);
        sum += sum_part;
        if (sum_part != 0) {
          std::cout << "At sign: " << c << " - " << sum_part << std::endl;
        }

        sum_part = SearchLeftVal(string_set.at(1), idx);
        sum += sum_part;
        if (sum_part != 0) {
          std::cout << "At sign: " << c << " - " << sum_part << std::endl;
        }

      }
      idx++;
    }

  }

  return sum;
}

int main() {
  std::cout << "Hello AoC Day 3! \n" << std::endl;

  const char *file_name = "../data/day_03_input.txt";
  std::ifstream file = OpenFile(file_name);
  int calibration_sum = ReadAndProcessGames(file);
  std::cout << "The engine schematic sum is: \033[32m" << calibration_sum << "\033[0m" << std::endl;
  CloseFile(file);
  return 0;

}