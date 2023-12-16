
##
# Created by JS-Robotics on 16.12.23.
##


class RaceData:
    def __init__(self, time, distance):
        self.time = time
        self.distance = distance


kRaceDataExample = [RaceData(71530, 940200)]

kRaceDataInput = [RaceData(53837288, 333163512891532)]


def get_distance(charge_time, tot_time):
    vel = charge_time
    distance = vel * (tot_time - charge_time)
    return distance


def process_data():
    wins = []

    for race_data in kRaceDataInput:
        i = 1
        k = 0
        while race_data.time - i > 0:
            i += 1
            if get_distance(i, race_data.time) > race_data.distance:
                k += 1
        if k > 0:
            wins.append(k)

    accumulated_sum = 1
    for win in wins:
        accumulated_sum *= win

    return accumulated_sum


if __name__ == "__main__":
    print("Hello AoC Day 6!\n")
    sum_result = process_data()
    print(f"The total Race sum is: {sum_result}")
