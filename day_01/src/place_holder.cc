#include <iostream>
#include <regex>
#include <string>
#include <vector>



int main() {
  std::vector<std::string> inputs = {
      "two1nine",
      "eightwothree",
      "abcone2threexyz",
      "xtwone3four",
      "4nineeightseven2",
      "zoneight234",
      "7pqrstsixteen"
  };

  std::regex pattern("(?=(zero|one|two|three|four|five|six|seven|eight|nine|\\d))");

  for (const std::string& input : inputs) {

    std::sregex_iterator iter(input.begin(), input.end(), pattern);
    std::sregex_iterator end;

    std::string part{};
    while (iter != end) {
      std::smatch match = *iter;
      part += match.str(1) + " ";
      ++iter;
    }

    std::cout << input << " - Matched: [" << part <<  "]" << std::endl;
  }

  return 0;
}
