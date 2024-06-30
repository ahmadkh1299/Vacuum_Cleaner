#include "Vacuum.h"
#include <iostream>
#include <utility>
Vacuum::Vacuum()
        : max_battery_vacuum(0), max_mission_vacuum(0), curr_battery_level(0), curr_steps_num(0) {}

// User-defined constructor
Vacuum::Vacuum(House  h, int max_battery, int max_mission, std::pair<int, int>  dock, std::pair<int, int>  location, int battery_level, int steps_num):
               house(std::move(h)), max_battery_vacuum(max_battery), max_mission_vacuum(max_mission),
               docking_station(std::move(dock)), curr_location(std::move(location)),
               curr_battery_level(battery_level), curr_steps_num(steps_num) {}

void Vacuum::chargeBattery() {
    if(located_at_D()) {
        int steps_on_docking = curr_steps_num; // Steps taken to reach docking station
        curr_battery_level = steps_on_docking + (curr_steps_num * (max_battery_vacuum / 20));
        std::cout << curr_battery_level << " steps.\n";

    }
}

void Vacuum::update() {
    //after one step update the current steps number and the battery level
    Vacuum::setCurrStepsNum(Vacuum::getCurrStepsNum()+1);
    Vacuum::setCurrBatteryLevel(Vacuum::getCurrBatteryLevel()-1);
}

bool Vacuum::Max_allowed_steps() const{ // lesh const??
    return getCurrStepsNum()==getMaxMissionVacuum();
}
bool Vacuum::located_at_D() const {
    return (getCurrLocation().first==getDockingStation().first && getCurrLocation().second==getDockingStation().second);
}