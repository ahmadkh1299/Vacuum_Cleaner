#include "Algorithm.h"
#include <utility>
#include <iostream>

Algorithm::Algorithm(int width, int length, std::pair<int, int> curr_location, std::pair<int, int> dock_station)
        :house_width(width), house_length(length), current_location(std::move(curr_location)), docking_station(std::move(dock_station)) {
    // Initialize your algorithm here if needed
}

MoveDirection Algorithm::nextMove(int dirt_level, bool wall_north, bool wall_east, bool wall_south, bool wall_west) {
    if (dirt_level > 0 & dirt_level< 9) {
        return MoveDirection::Stay; // Clean the current location
    } else {
        std::vector<MoveDirection> possible_moves;
        if (!wall_north) possible_moves.push_back(MoveDirection::North);
        if (!wall_east) possible_moves.push_back(MoveDirection::East);
        if (!wall_south) possible_moves.push_back(MoveDirection::South);
        if (!wall_west) possible_moves.push_back(MoveDirection::West);

        if (possible_moves.empty()) {
            return MoveDirection::Stay;
        } else {
            std::uniform_int_distribution<int> distribution(0, possible_moves.size() - 1);
            int index = distribution(generator);
            return possible_moves[index];
        }
    }
}

MoveDirection Algorithm::reverseDirection(MoveDirection direction) {
    switch (direction) {
        case MoveDirection::North:
            return MoveDirection::South;
        case MoveDirection::East:
            return MoveDirection::West;
        case MoveDirection::South:
            return MoveDirection::North;
        case MoveDirection::West:
            return MoveDirection::East;
        case MoveDirection::Stay:
        default:
            return MoveDirection::Stay;
    }
}

std::stack<MoveDirection> Algorithm::findPathToDocking(const std::stack<MoveDirection>& history) {
    std::stack<MoveDirection> path;

    // Reverse the history to find the path back
    std::stack<MoveDirection> reverse_history = history;
    while (!reverse_history.empty()) {
        path.push(reverseDirection(reverse_history.top()));
        reverse_history.pop();
    }

    return path;
}

MoveDirection Algorithm::getMoveDirection(std::pair<int, int> from, std::pair<int, int> to) {
    int dx = to.first - from.first;
    int dy = to.second - from.second;

    if (dx == -1 && dy == 0) {
        return MoveDirection::North;
    } else if (dx == 1 && dy == 0) {
        return MoveDirection::South;
    } else if (dx == 0 && dy == 1) {
        return MoveDirection::East;
    } else if (dx == 0 && dy == -1) {
        return MoveDirection::West;
    } else {
        return MoveDirection::Stay;
    }
}
