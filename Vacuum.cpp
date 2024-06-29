//
// Created by Mariam on 6/29/2024.
//

#include "Vacuum.h"
#include <iostream>
Vacuum::Vacuum()
    : max_battery_vacuum(0), max_mission_vacuum(0), curr_battery_level(0), curr_steps_num(0) {}

// User-defined constructor
Vacuum::Vacuum(const House& h, int max_battery, int max_mission, const std::pair<int, int>& dock,
               const std::pair<int, int>& location, int battery_level, int steps_num)
    : house(h), max_battery_vacuum(max_battery), max_mission_vacuum(max_mission),
      docking_station(dock), curr_location(location), curr_battery_level(battery_level),
      curr_steps_num(steps_num) {}
void Vacuum::chargeBattery() {
    int steps_on_docking = curr_steps_num; // Steps taken to reach docking station
    curr_battery_level = steps_on_docking + (curr_steps_num * (max_battery_vacuum / 20));
    std::cout << curr_battery_level << " steps.\n";
}
