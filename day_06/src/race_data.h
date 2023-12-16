///
/// Created by JS-Robotics on 16-Dec-23.
///

#ifndef AOC_DAY_SIX_DAY_06_SRC_DATA_RACE_DATA_H_
#define AOC_DAY_SIX_DAY_06_SRC_DATA_RACE_DATA_H_

struct RaceData {
  int time;
  int distance;
};

const RaceData kRaceDataDev[] = {
    {7, 9}
};

const RaceData kRaceDataExample[] = {
    {7, 9},
    {15, 40},
    {30, 200}
};

const RaceData kRaceDataInput[] = {
    {53, 333},
    {83, 1635},
    {72, 1289},
    {88, 1532}
};

#endif //AOC_DAY_SIX_DAY_06_SRC_DATA_RACE_DATA_H_
