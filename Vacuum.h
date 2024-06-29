//
// Created by Mariam on 6/29/2024.
//

#ifndef VACUUM_H
#define VACUUM_H

#include "House.h"
#include <vector>
#include <string>
#include <stdexcept>
#include <utility>

class Vacuum {
private:
    House house;
    int max_battery_vacuum;
    int max_mission_vacuum;
    std::pair<int, int> docking_station;
    std::pair<int, int> curr_location;
    int curr_battery_level;
    int curr_steps_num;

public:

    Vacuum();

    // User-defined constructor
    Vacuum(const House& h, int max_battery, int max_mission, const std::pair<int, int>& dock,
           const std::pair<int, int>& location, int battery_level, int steps_num);
    // Getters
    House getHouse() const {
        return house;
    }

    int getMaxBatteryVacuum() const {
        return max_battery_vacuum;
    }

    int getMaxMissionVacuum() const {
        return max_mission_vacuum;
    }

    std::pair<int, int> getDockingStation() const {
        return docking_station;
    }

    std::pair<int, int> getCurrLocation() const {
        return curr_location;
    }

    int getCurrBatteryLevel() const {
        return curr_battery_level;
    }

    int getCurrStepsNum() const {
        return curr_steps_num;
    }

    // Setters
    void setHouse(const House& h) {
        house = h;
    }

    void setMaxBatteryVacuum(int battery) {
        max_battery_vacuum = battery;
    }

    void setMaxMissionVacuum(int mission) {
        max_mission_vacuum = mission;
    }

    void setDockingStation(const std::pair<int, int>& dock) {
        docking_station = dock;
    }

    void setCurrLocation(const std::pair<int, int>& location) {
        curr_location = location;
    }

    void setCurrBatteryLevel(int battery) {
        curr_battery_level = battery;
    }

    void setCurrStepsNum(int steps) {
        curr_steps_num = steps;
    }
    void chargeBattery();

};

#endif //VACUUM_H
