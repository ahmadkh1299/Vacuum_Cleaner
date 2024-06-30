#ifndef VACUUM_H
#define VACUUM_H

#include "House.h"
#include "Algorithm.h"
#include <stack>
#include <vector>

class Vacuum {
public:
    Vacuum(House& house, Algorithm& algorithm, int max_battery_steps, int max_mission_steps);

    void simulate();
    void outputResults(const std::string& output_file) const;

private:
    House& house;
    Algorithm& algorithm;
    int battery_steps;
    int max_battery_steps;
    int max_mission_steps;
    int total_steps;
    std::pair<int, int> current_location;
    std::stack<MoveDirection> history;

    bool move(MoveDirection direction);
    int getDirtLevel() const;
    bool isWall(MoveDirection direction) const;
    void chargeBattery();
    void logStep(MoveDirection direction);

    std::vector<std::string> log;
};

#endif // VACUUM_H
