///
/// Created by JS-Robotics on 16.12.23.
///


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <unordered_map>

enum class WinType {
  kHighCard,
  kOnePair,
  kTwoPairs,
  kThreeOfAKind,
  kFullHouse,
  kFourOfAKind,
  kFiveOfAKind
};

struct Hand {
  std::string cards;
  int bid{};
  WinType win_type = WinType::kHighCard;
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

WinType GetWinType(const std::string &cards) {

  //Get the count of each card in the hand
  std::unordered_map<char, int> count_of_cards;
  for (const char &card : cards) {
    count_of_cards[card]++;
  }

  // Print the counts for each unique character
  std::unordered_map<int, int> count_of_counts;
  for (const auto& pair : count_of_cards) {
    count_of_counts[pair.second]++;
  }

  const int FIVE_OF_A_KIND = 5;
  const int FOUR_OF_A_KIND = 4;
  const int THREE_OF_A_KIND = 3;
  const int TWO_OF_A_KIND = 2;

  if(count_of_counts[FIVE_OF_A_KIND] == 1){
//    std::cout << "Five of a kind" << std::endl;
    return WinType::kFiveOfAKind;
  }

  if(count_of_counts[FOUR_OF_A_KIND] == 1){
//    std::cout << "Four of a kind" << std::endl;
    return WinType::kFourOfAKind;
  }

  if(count_of_counts[THREE_OF_A_KIND] == 1 && count_of_counts[TWO_OF_A_KIND] == 1){
//    std::cout << "Full House" << std::endl;
    return WinType::kFullHouse;
  }

  if(count_of_counts[THREE_OF_A_KIND] == 1){
//    std::cout << "Three of a kind" << std::endl;
    return WinType::kThreeOfAKind;
  }

  if(count_of_counts[TWO_OF_A_KIND] == 2){
//    std::cout << "Two pairs" << std::endl;
    return WinType::kTwoPairs;
  }

  if(count_of_counts[TWO_OF_A_KIND] == 1){
//    std::cout << "One pair" << std::endl;
    return WinType::kOnePair;
  }

//  std::cout << "High card" << std::endl;
  return WinType::kHighCard;
}

Hand GetHand(const std::string &line) {
  Hand hand{};
  size_t space_pos = line.find(' ');
  if (space_pos != std::string::npos) {
    std::string str_part = line.substr(0, space_pos);
    int int_part = std::stoi(line.substr(space_pos + 1)); // Convert the substring to an integer
    hand.cards = str_part;
    hand.bid = int_part;
  } else {
    std::cerr << "Space character not found!" << std::endl;
  }

  hand.win_type = GetWinType(hand.cards);

  return hand;
}

int ReadAndProcess(std::ifstream &file) {

  int sum = 0;
  std::string line;
  std::vector<Hand> hands;

  while (std::getline(file, line)) {
    hands.emplace_back(GetHand(line));
  }

  for (const Hand &kHand : hands) {
//    std::cout << kHand.cards << " - " << kHand.bid << std::endl;
  }

  return sum;
}

int main() {
  std::cout << "Hello AoC Day 4! \n" << std::endl;

  const char *file_name = "../data/day_07_example.txt";
  std::ifstream file = OpenFile(file_name);
  int calibration_sum = ReadAndProcess(file);
  std::cout << "The cards total sum is: \033[32m" << calibration_sum << "\033[0m" << std::endl;
  CloseFile(file);
  return 0;

}