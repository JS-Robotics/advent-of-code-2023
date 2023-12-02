///
/// Created by JS-Robotics on 01.12.23.
///


#include <iostream>
#include <string>
#include <fstream>
#include <vector>

template<typename T>
struct VectorTwo {
  T first;
  T second;

  // Constructor that initializes first and second
  VectorTwo(T first_init, T second_init) : first(first_init), second(second_init) {}
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

int CharToInt(char c) {
  return c - '0';
}

VectorTwo<int> GetNumbersFromString(const std::string &string) {
  std::vector<int> numbers;
  char max_num_as_char = '9';
  char min_num_as_char = '0';

  for (char c : string) {
    if (min_num_as_char <= c && c <= max_num_as_char) {
      numbers.emplace_back(static_cast<int>(CharToInt(c)));
    }
  }

  if (numbers.size() == 1) {
    return VectorTwo<int>{numbers.at(0), numbers.at(0)};
  } else {
    return VectorTwo<int>{numbers.at(0), numbers.at(numbers.size() - 1)};
  }
}

int GetValue(VectorTwo<int> &the_vector) {
  int prem_val = the_vector.first * 10 + the_vector.second;
  return prem_val;
}

int ReadAndPrintLines(std::ifstream &file) {
  std::string line;
  std::vector<VectorTwo<int>> extracted_numbers;
  while (std::getline(file, line)) {
    VectorTwo<int> vector_two = GetNumbersFromString(line);
    extracted_numbers.emplace_back(vector_two);
  }

  int sum = 0;
  for (auto number : extracted_numbers) {
    sum += GetValue(number);
  }

  return sum;
}

int main() {
  std::cout << "Hello AoC Day 1! \n" << std::endl;

  const char *file_name = "../data/day_01_input.txt";
  std::ifstream file = OpenFile(file_name);
  int calibration_sum = ReadAndPrintLines(file);
  std::cout << "The calibration sum is: \033[32m" << calibration_sum << "\033[0m" << std::endl;
  CloseFile(file);
  return 0;

}