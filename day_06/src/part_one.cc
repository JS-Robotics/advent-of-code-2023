///
/// Created by JS-Robotics on 16.12.23.
///


#include <iostream>
#include <vector>
#include <regex>
#include <sstream>

#include "race_data.h"

int GetDistance(int charge_time, int tot_time) {
  int vel = charge_time;
  int distance = vel * (tot_time - charge_time);
  return distance;
}

int ProcessData() {
  std::vector<int> wins;

  for (const RaceData &kRaceData : kRaceDataInput) {
    int i = 1;
    int k = 0;
    while (kRaceData.time - i > 0) {
      i++;
      if (GetDistance(i, kRaceData.time) > kRaceData.distance) {
        k++;
      }
    }
    if (k > 0) {
      wins.emplace_back(k);
    }
  }

  int sum = 1;
  for (int win : wins) {
    sum = sum * win;
  }

  return sum;
}

int main() {
  std::cout << "Hello AoC Day 6! \n" << std::endl;
  int sum = ProcessData();
  std::cout << "The total Race sum is: \033[32m" << sum << "\033[0m" << std::endl;
  return 0;

}