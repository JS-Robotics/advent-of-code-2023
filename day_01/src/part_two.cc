///
/// Created by JS-Robotics on 01.12.23.
///


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <map>

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

int FromStringToInt(const std::string &matched_string){
  // Define a map to map string representations to their integer values
  std::map<std::string, int> string_to_value = {
      {"zero", 0},
      {"0", 0},
      {"one", 1},
      {"1", 1},
      {"two", 2},
      {"2", 2},
      {"three", 3},
      {"3", 3},
      {"four", 4},
      {"4", 4},
      {"five", 5},
      {"5", 5},
      {"six", 6},
      {"6", 6},
      {"seven", 7},
      {"7", 7},
      {"eight", 8},
      {"8", 8},
      {"nine", 9},
      {"9", 9}
  };

  // Check if the matched string is in the map, and return its value; otherwise, return 0
  auto it = string_to_value.find(matched_string);
  if (it != string_to_value.end()) {
    return it->second;
  } else {
    return 0;
  }
}

VectorTwo<int> GetNumbersFromString(const std::string &string) {
  std::vector<int> numbers;
  char max_num_as_char = '9';
  char min_num_as_char = '0';

  std::string input = string;
  std::regex pattern("(?=(zero|one|two|three|four|five|six|seven|eight|nine|\\d))");
  std::sregex_iterator iter(input.begin(), input.end(), pattern);
  std::sregex_iterator end;

  std::string part{};
  std::string part_as_value{};
  while (iter != end) {
    std::smatch match = *iter;
    part += match.str(1) + " ";
    int value = FromStringToInt(match.str(1));
    part_as_value += std::to_string(value) + " ";
    numbers.emplace_back(value);
    ++iter;
  }
//  std::cout << input << " - Matched: [" << part << "] - " << part_as_value << std::endl;



  if (numbers.size() == 1) {
    return VectorTwo<int>{numbers.at(0), numbers.at(0)};
  } else if (numbers.size() >= 2) {
    return VectorTwo<int>{numbers.at(0), numbers.at(numbers.size() - 1)};
  } else {
    std::cout << "Trying to return no numbers, add handling for this" << std::endl;
    return VectorTwo<int>{0, 0};
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