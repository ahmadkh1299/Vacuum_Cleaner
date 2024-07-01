#include "Vacuum.h"
#include <fstream>
#include <iostream>

Vacuum::Vacuum(House& house, Algorithm& algorithm, int max_battery_steps, int max_mission_steps)
        : house(house), algorithm(algorithm), battery_steps(max_battery_steps), max_battery_steps(max_battery_steps),
          max_mission_steps(max_mission_steps), total_steps(0), current_location(house.getDockingStation()) {}


void Vacuum::simulate() {
    while (total_steps < max_mission_steps) {
        if (battery_steps <= history.size()) {
            std::stack<MoveDirection> path_to_docking = algorithm.findPathToDocking(history);
            printPath(path_to_docking);
            while ((!path_to_docking.empty())  && total_steps<max_mission_steps) {
                move(path_to_docking.top());
                path_to_docking.pop();
                if (!located_at_D()) {
                    update();
                }
            }
            if (located_at_D()) {
                chargeBattery();
                history = std::stack<MoveDirection>();
            }
            // Clear history after recharging
           // continue;
        } else {

            int dirt_level = getDirtLevel();
            bool wall_north = isWall(MoveDirection::North);
            bool wall_east = isWall(MoveDirection::East);
            bool wall_south = isWall(MoveDirection::South);
            bool wall_west = isWall(MoveDirection::West);

            MoveDirection direction = algorithm.nextMove(dirt_level, wall_north, wall_east, wall_south, wall_west);
            if (direction == MoveDirection::Stay && dirt_level > 0 && (!located_at_D())) {
                house.getHouseMatrix()[current_location.first][current_location.second]--;
                house.decreaseTotaldirt();
                //we have to update the steps and battery
            }

            logStep(direction);
            if (!move(direction)) {
                std::cerr << "Error: Move failed!" << std::endl;
                break;
            }
            update();
/*        if (located_at_D()) {
            chargeBattery();
        }*/
            if (battery_steps < 0) {
                std::cerr << "Battery exhausted!" << std::endl;
                break;
            }

            bool all_clean = true;
            for (const auto &row: house.getHouseMatrix()) {
                for (int cell: row) {
                    if (cell > 0 && cell < 20) {
                        all_clean = false;
                        break;
                    }
                }
                if (!all_clean) break;
            }

            if (all_clean && current_location == house.getDockingStation()) {
                std::cout << "Mission accomplished!" << std::endl;
                break;
            }
        }
    }
}

void Vacuum::outputResults(const std::string& output_file) const {
    std::ofstream file(output_file);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open output file: " + output_file);
    }

    for (const auto& step : log) {
        file << step << std::endl;
    }

    file << "Total steps: " << total_steps << std::endl;

    int remaining_dirt = 0;
    for (const auto& row : house.getHouseMatrix()) {
        for (int cell : row) {
            if (cell > 0 && cell <= 9) {
                remaining_dirt += cell;
            }
        }
    }

    file << "Remaining dirt: " << remaining_dirt << std::endl;
    file << "Vacuum cleaner status: " << (battery_steps <= 0 ? "Dead" : "Alive") << std::endl;
    file << "Mission status: " << (remaining_dirt == 0 && current_location == house.getDockingStation() ? "Success" : "Failure") << std::endl;

    file.close();
}

bool Vacuum::move(MoveDirection direction) {
    int new_x = current_location.first;
    int new_y = current_location.second;

    switch (direction) {
        case MoveDirection::North:
            new_x -= 1;
            break;
        case MoveDirection::East:
            new_y += 1;
            break;
        case MoveDirection::South:
            new_x += 1;
            break;
        case MoveDirection::West:
            new_y -= 1;
            break;
        case MoveDirection::Stay:
        default:
            return true;
    }
    if (new_x >= 0 && new_x < house.getLength() && new_y >= 0 && new_y < house.getWidth() && house.getHouseMatrix()[new_x][new_y] != -1) {
        current_location = {new_x, new_y};
        history.push(direction);
        return true;
    } else {
        return false;
    }
}

int Vacuum::getDirtLevel() const {
    return house.getHouseMatrix()[current_location.first][current_location.second];
}

bool Vacuum::isWall(MoveDirection direction) const {
    int new_x = current_location.first;
    int new_y = current_location.second;

    switch (direction) {
        case MoveDirection::North:
            new_x -= 1;
            break;
        case MoveDirection::East:
            new_y += 1;
            break;
        case MoveDirection::South:
            new_x += 1;
            break;
        case MoveDirection::West:
            new_y -= 1;
            break;
        case MoveDirection::Stay:
        default:
            return false;
    }

    return (new_x < 0 || new_x >= house.getLength() || new_y < 0 || new_y >= house.getWidth() || house.getHouseMatrix()[new_x][new_y] == -1);
}

void Vacuum::chargeBattery() { // charging
    float ch = max_battery_steps/20;
    while (battery_steps < max_battery_steps && total_steps < max_mission_steps) {
        battery_steps += ch;
        total_steps++;
    }
}

std::string moveDirectionToString(MoveDirection direction) {
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

void Vacuum::printPath(const std::stack<MoveDirection>& path) const {
    std::stack<MoveDirection> temp_path = path;

    std::cout << "class vacu Path: ";
    while (!temp_path.empty()) {
        MoveDirection move = temp_path.top();
        temp_path.pop();
        std::cout << moveDirectionToString(move) << " ";
    }
    std::cout << std::endl;
}

bool Vacuum::located_at_D() const {
    return (current_location.first==house.getDockingStation().first && current_location.second==house.getDockingStation().second);
}

void Vacuum::logStep(MoveDirection direction) {
    log.push_back(moveDirectionToString(direction));
}
void Vacuum::update() {
    //after one step update the current steps number and the battery level
    //Vacuum::setCurrStepsNum(Vacuum::total_steps()+1);
    //Vacuum::setbattery_steps(Vacuum::battery_steps-1);
    total_steps++;
    battery_steps--;

}