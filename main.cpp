#include "House.h"
#include "Algorithm.h"
#include "Vacuum.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class ConfigReader {
public:
    ConfigReader(const std::string &file_path) {
        readFromFile(file_path);
        parseConfig();
    }

    const std::vector<std::string>& getLayout() const {
        return layout;
    }

    int getMaxBatterySteps() const {
        return max_battery_steps;
    }

    int getMaxMissionSteps() const {
        return max_mission_steps;
    }

private:
    std::vector<std::string> layout;
    int max_battery_steps;
    int max_mission_steps;

    void readFromFile(const std::string &file_path) {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + file_path);
        }
        std::string line;
        while (std::getline(file, line)) {
            layout.push_back(line);
        }
        file.close();
    }

    void parseConfig() {
        std::istringstream iss(layout.back());
        layout.pop_back();
        if (!(iss >> max_battery_steps >> max_mission_steps)) {
            throw std::runtime_error("Failed to parse configuration from file");
        }
    }
};

int main() {
    std::string input_file = "C:\\Users\\97250\\Desktop\\TAU\\5th\\Advanced Programing\\HW\\test1.txt";
    ConfigReader config(input_file);
    House house(config.getLayout());
    Algorithm algorithm(house.getWidth(), house.getLength(), house.getDockingStation(), house.getDockingStation());
    Vacuum vacuum(house, algorithm, config.getMaxBatterySteps(), config.getMaxMissionSteps());

    vacuum.simulate();
    vacuum.outputResults("C:\\Users\\97250\\Desktop\\TAU\\5th\\Advanced Programing\\HW\\output.txt");

    return 0;
}
