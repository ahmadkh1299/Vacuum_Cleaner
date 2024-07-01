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
    std::pair<int, int> getcurrent_location(){ return current_location;}
    int getx() const {
        return current_location.first;
    }
    int gety() const{ return current_location.second; }
    void setbattery_steps(int battery) {
        battery_steps = battery;
    }
    void setCurrStepsNum(int steps) {
        total_steps = steps;
    }


    bool move(MoveDirection direction);
    int getDirtLevel() const;
    bool isWall(MoveDirection direction) const;
    void chargeBattery();
    void logStep(MoveDirection direction);
    bool located_at_D() const;
    void update();
    std::vector<std::string> log;
};

#endif // VACUUM_H
