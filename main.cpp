#include "House.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std; //not recommended

class ConfigReader {
public:
    ConfigReader(const std::string &file_path) {
        readFromFile(file_path);
        parseConfig();
    }

    const std::vector<std::string>& getLayout() const {
        return layout;
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
    std::string test1 = "C:\\Users\\97250\\Desktop\\TAU\\5th\\Advanced Programing\\HW\\test1.txt";
    ConfigReader config(test1);
    House h1(config.getLayout());
    std::vector<std::vector<int>> matrix1 = h1.getHouseMatrix();
    for (const auto& row : matrix1) {
        for (int cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
    std::pair<int, int> dockingStationCoords = h1.getDockingStation();
    std::cout << "Docking Station Coordinates: (" << dockingStationCoords.first
              << ", " << dockingStationCoords.second << ")" << std::endl;
    return 0;
}