#include "Algorithm.h"
#include <utility>
#include <iostream>
#include <chrono>

Algorithm::Algorithm(int width, int length, std::pair<int, int> curr_location, std::pair<int, int> dock_station)
        : house_width(width), house_length(length), current_location(std::move(curr_location)), docking_station(std::move(dock_station)) {
    // Initialize your algorithm here if needed
    auto seed = std::chrono::system_clock::now().time_since_epoch().count(); // Added this line
    generator.seed(seed);
}

MoveDirection Algorithm::nextMove(int dirt_level, bool wall_north, bool wall_east, bool wall_south, bool wall_west) {
    if (dirt_level > 0 && dirt_level < 9) {
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
    std::stack<MoveDirection> temp_history = history;  // Copy of the original history stack to preserve order
    std::stack<MoveDirection> reversed = std::stack<MoveDirection>();
    while (!temp_history.empty()) {
        reversed.push(temp_history.top());
        temp_history.pop();
    }
    temp_history = reversed;
    reversed = std::stack<MoveDirection>();
    while (!temp_history.empty()) {
        MoveDirection move = reverseDirection(temp_history.top());
        temp_history.pop();
        if (move != MoveDirection::Stay) {
            reversed.push(move);
        }
    }
    return reversed;
}


void Algorithm::printPath(const std::stack<MoveDirection>& path) const {
    std::stack<MoveDirection> temp_path = path;

    std::cout << "class algo Path: ";
    while (!temp_path.empty()) {
        MoveDirection move = temp_path.top();
        temp_path.pop();
        std::cout << moveDirectionToString1(move) << " ";
    }
    std::cout << std::endl;
}

std::string moveDirectionToString1(MoveDirection direction) {
    switch (direction) {
        case MoveDirection::North:
            return "North";
        case MoveDirection::East:
            return "East";
        case MoveDirection::South:
            return "South";
        case MoveDirection::West:
            return "West";
        case MoveDirection::Stay:
            return "Stay";
        default:
            return "Unknown";
    }
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


