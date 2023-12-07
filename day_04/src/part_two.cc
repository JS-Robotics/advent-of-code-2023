///
/// Created by JS-Robotics on 01.12.23.
///


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>

struct CardSet {
  int card{};
  int matches{};
  std::vector<int> card_numbers{};
  std::vector<int> winning_numbers{};
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

std::vector<int> GetCards(const std::string &line) {
  std::vector<int> numbers;
  std::regex pattern(": ([0-9 ]+)");

  std::sregex_iterator iter(line.begin(), line.end(), pattern);
  std::sregex_iterator end;

  std::string numbers_on_card;
  while (iter != end) {
    std::smatch match = *iter;
    numbers_on_card = match.str(1);
    ++iter;
  }

  std::regex pattern_number("\\d+");
  std::sregex_iterator iter_two(numbers_on_card.begin(), numbers_on_card.end(), pattern_number);
  std::sregex_iterator end_two;

  while (iter_two != end_two) {
    std::smatch match = *iter_two;
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
    ++iter;
  }

  std::regex pattern_number("\\d+");
  std::sregex_iterator iter_two(winning_numbers.begin(), winning_numbers.end(), pattern_number);
  std::sregex_iterator end_two;

  while (iter_two != end_two) {
    std::smatch match = *iter_two;
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
  std::vector<CardSet> card_sets;
  std::vector<std::string> input;

  //Store game data into a vector of strings to process afterward
  while (std::getline(file, line)) {
    input.emplace_back(line);
  }

  //Store all Cards and their data
  int card = 1;
  for (const std::string &game : input) {
    CardSet card_set;
    card_set.card = card;
    card_set.card_numbers = GetCards(game);
    card_set.winning_numbers = GetWinningNumbers(game);
    card_sets.emplace_back(card_set);
    card++;
  }


  //Store all matches for a card and winning numbers
  for (CardSet &kCardSet : card_sets) {
    std::string string = std::to_string(kCardSet.card) + " : ";
    for (int number : kCardSet.card_numbers) {
      string += " - " + std::to_string(number);
    }
    std::cout << string << std::endl;

    string = std::to_string(kCardSet.card) + " : ";
    for (int number : kCardSet.winning_numbers) {
      string += " - " + std::to_string(number);
    }
    std::cout << string << std::endl;

    int matches = 0;
    for (int number : kCardSet.card_numbers) {
      for (int winning_number : kCardSet.winning_numbers) {
        if (number == winning_number) {
          matches++;
        }
      }

    }
    kCardSet.matches = matches;
    std::cout << kCardSet.card << " : " << kCardSet.matches << std::endl;
  }

  std::vector<CardSet> total_cards = card_sets;
  std::vector<CardSet> added_cards = card_sets;

  bool new_card = true;
  while (new_card) {
    std::vector<CardSet> prelim_cards = std::move(added_cards);
    added_cards.clear();
    new_card = false;
    for (CardSet &kCardSet : prelim_cards) {
      if (kCardSet.matches > 0) {
        new_card = true;
        std::cout << "at: " << kCardSet.card << std::endl;
        for (int i = kCardSet.card + 1; i < kCardSet.card +1+ kCardSet.matches; i++) {
          std::cout << "adding: " << i << std::endl;
          added_cards.emplace_back(card_sets.at(i));
        }
      }
    }
    for (const CardSet &kCardSet : added_cards) {
      total_cards.emplace_back(kCardSet);
    }
  }

  for (const CardSet &card_set_1 : added_cards) {
    std::cout << card_set_1.card << std::endl;
  }

  // Print the modified card_sets
  for (const auto &card_set : total_cards) {
    std::cout << "Card: " << card_set.card << ", Matches: " << card_set.matches << std::endl;
  }

  return sum;
}

int main() {
  std::cout << "Hello AoC Day 4! \n" << std::endl;

  const char *file_name = "../data/day_04_example.txt";
  std::ifstream file = OpenFile(file_name);
  int calibration_sum = ReadAndProcess(file);
  std::cout << "The cards total sum is: \033[32m" << calibration_sum << "\033[0m" << std::endl;
  CloseFile(file);
  return 0;

}