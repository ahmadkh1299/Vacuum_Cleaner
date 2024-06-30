#include "Algorithm.h"

#include <utility>

Algorithm::Algorithm(int width, int length, std::pair<int, int> curr_location, std::pair<int, int> dock_station)
        :house_width(width), house_length(length), current_location(std::move(curr_location)), docking_station(std::move(dock_station)) {
    // Initialize your algorithm here if needed
}

MoveDirection Algorithm::nextMove(int dirt_level, bool wall_north, bool wall_east, bool wall_south, bool wall_west) {
    // Simulate decision making process
    if (dirt_level > 0) {
        return MoveDirection::Stay; // Clean the current location
    } else {
        // Move randomly without hitting walls
        std::vector<MoveDirection> possible_moves;
        if (!wall_north) possible_moves.push_back(MoveDirection::North);
        if (!wall_east) possible_moves.push_back(MoveDirection::East);
        if (!wall_south) possible_moves.push_back(MoveDirection::South);
        if (!wall_west) possible_moves.push_back(MoveDirection::West);

        if (possible_moves.empty()) {
            return MoveDirection::Stay; // No valid moves, stay in place
        } else {
            std::uniform_int_distribution<int> distribution(0, possible_moves.size() - 1);
            int index = distribution(generator);
            return possible_moves[index];
        }
    }
}


std::stack<MoveDirection> Algorithm::findPathToDocking() {
    std::queue<std::pair<int, int>> queue;
    std::vector<std::vector<std::pair<int, int>>> parent(house_length, std::vector<std::pair<int, int>>(house_width, {-1, -1}));
    std::vector<std::vector<bool>> visited(house_length, std::vector<bool>(house_width, false));
    std::stack<MoveDirection> path;

    queue.push(current_location);
    visited[current_location.first][current_location.second] = true;

    while (!queue.empty()) {
        std::pair<int, int> current = queue.front();
        queue.pop();

        if (current == docking_station) {
            std::pair<int, int> step = current;
            while (step != current_location) {
                std::pair<int, int> prev_step = parent[step.first][step.second];
                path.push(getMoveDirection(prev_step, step));
                step = prev_step;
            }
            return path;
        }

        for (const auto& dir : directions) {
            int new_x = current.first + dir.first;
            int new_y = current.second + dir.second;

            if (new_x >= 0 && new_x < house_length && new_y >= 0 && new_y < house_width && !visited[new_x][new_y]) {
                queue.push({new_x, new_y});
                visited[new_x][new_y] = true;
                parent[new_x][new_y] = current;
            }
        }
    }

    return path; // In case no path found, return an empty stack
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