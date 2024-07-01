#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stack>
#include <utility>
#include <vector>
#include <random>
#include <string>

enum class MoveDirection {
    North,
    East,
    South,
    West,
    Stay
};

class Algorithm {
public:
    Algorithm(int width, int length, std::pair<int, int> curr_location, std::pair<int, int> dock_station);

    MoveDirection nextMove(int dirt_level, bool wall_north, bool wall_east, bool wall_south, bool wall_west);
    std::stack<MoveDirection> findPathToDocking(const std::stack<MoveDirection>& history);
    void printPath(const std::stack<MoveDirection>& path) const;
    static MoveDirection reverseDirection(MoveDirection direction);
    static MoveDirection getMoveDirection(std::pair<int, int> from, std::pair<int, int> to);

private:
    int house_width;
    int house_length;
    std::pair<int, int> current_location;
    std::pair<int, int> docking_station;
    std::default_random_engine generator;
};

std::string moveDirectionToString1(MoveDirection direction);

#endif // ALGORITHM_H
