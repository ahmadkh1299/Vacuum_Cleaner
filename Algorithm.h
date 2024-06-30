#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <queue>
#include <random>
#include <stack>
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
    Algorithm(int width, int length, std::pair<int, int> curr_location, std::pair<int, int> docking_station);
    MoveDirection nextMove(int dirt_level, bool wall_north, bool wall_east, bool wall_south, bool wall_west);
    std::stack<MoveDirection> findPathToDocking();

private:
    int house_width;
    int house_length;
    std::pair<int, int> current_location;
    std::pair<int, int> docking_station;
    std::vector<std::vector<bool>> visited;

    std::default_random_engine generator;
    std::pair<int, int> directions[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // North, East, South, West

    MoveDirection getMoveDirection(std::pair<int, int> from, std::pair<int, int> to);
};

#endif // ALGORITHM_H
