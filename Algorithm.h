#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <queue>
#include <random>
#include <utility>

enum class MoveDirection {
    North,
    East,
    South,
    West,
    Stay
};

class Algorithm {
public:
    Algorithm(int initial_battery, int width, int length);

    MoveDirection nextMove(int dirt_level, bool wall_north, bool wall_east, bool wall_south, bool wall_west);
    void updateLocation(int x, int y);

    void findShortestPathToDocking();
    MoveDirection getMoveDirection(std::pair<int, int> from, std::pair<int, int> to);

    bool isAtDockingStation() const;
    int getBattery() const;
    bool isBatteryExhausted() const;

private:
    int battery;
    int house_width;
    int house_length;
    std::pair<int, int> current_location;
    std::pair<int, int> docking_station;
    std::vector<std::vector<bool>> visited;
    std::queue<MoveDirection> path_to_docking;

    std::default_random_engine generator;
};

#endif // ALGORITHM_H
