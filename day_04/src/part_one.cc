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

std::vector<int> GetCards(const std::string &line) {
  std::vector<int> numbers;
  std::regex pattern(": ([0-9 ]+)");

  std::sregex_iterator iter(line.begin(), line.end(), pattern);
  std::sregex_iterator end;

  if (iter->size() == 1) {
    std::cout << "I am 1" << std::endl;
  }
  std::string numbers_on_card;
  while (iter != end) {
    std::smatch match = *iter;
    numbers_on_card = match.str(1);
//    std::cout << match.str(1) << std::endl;
    ++iter;
  }

  std::regex pattern_number("\\d+");
  std::sregex_iterator iter_two(numbers_on_card.begin(), numbers_on_card.end(), pattern_number);
  std::sregex_iterator end_two;

  while (iter_two != end_two) {
    std::smatch match = *iter_two;
//    std::cout << match.str() << std::endl;
    numbers.emplace_back(std::stoi(match.str()));
    ++iter_two;
  }

  return numbers;
}

std::vector<int> GetWinningNumbers(const std::string &line) {
  std::vector<int> numbers;
  std::regex pattern("\\| ([0-9 ]+)");

  std::sregex_iterator iter(line.begin(), line.end(), pattern);
  std::sregex_iterator end;

  std::string winning_numbers;
  while (iter != end) {
    std::smatch match = *iter;
    winning_numbers = match.str(1);
//    std::cout << match.str(1) << std::endl;
    ++iter;
  }

  std::regex pattern_number("\\d+");
  std::sregex_iterator iter_two(winning_numbers.begin(), winning_numbers.end(), pattern_number);
  std::sregex_iterator end_two;

  while (iter_two != end_two) {
    std::smatch match = *iter_two;
//    std::cout << match.str() << std::endl;
    numbers.emplace_back(std::stoi(match.str()));
    ++iter_two;
  }

  return numbers;
}

int ReadAndProcess(std::ifstream &file) {

  int sum = 0;
  std::string line;
  std::vector<int> card_numbers;
  std::vector<int> winning_numbers;

  while (std::getline(file, line)) {
//    std::cout << line << std::endl;
    card_numbers = GetCards(line);
    winning_numbers = GetWinningNumbers(line);
    int matches = 0;
    for (int number : card_numbers) {

      for (int winning_number : winning_numbers) {
        if (number == winning_number) {
          matches++;
        }
      }
    }

    int sum_part = 0;
    if (matches > 0) {
      for (int i = 1; i <= matches; i++) {
        if (i == 1) {
          sum_part = 1;
        } else {
          sum_part = sum_part * 2;
        }
//        std::cout << "Matches: " << matches << " points: " << sum_part << std::endl;
      }

      sum += sum_part;
//      std::cout << "sum is: " << sum << std::endl;
    }

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

  const char *file_name = "../data/day_04_input.txt";
  std::ifstream file = OpenFile(file_name);
  int calibration_sum = ReadAndProcess(file);
  std::cout << "The cards total sum is: \033[32m" << calibration_sum << "\033[0m" << std::endl;
  CloseFile(file);
  return 0;

}