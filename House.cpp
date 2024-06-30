#include "House.h"

House::House()
        : docking_station(-1, -1), width(0), length(0) {}

House::House(const std::vector<std::string>& layout_v)
        : docking_station(-1, -1), width(0), length(0) {
    initializeMatrix(layout_v);
    findDockingStation();
}

void House::initializeMatrix(const std::vector<std::string>& layout_v) {
    length = static_cast<int>(layout_v.size());
    width = static_cast<int>(layout_v[0].size());
    house_matrix.resize(length, std::vector<int>(width, 0));

    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < width; ++j) {
            char cell = layout_v[i][j];
            if (cell == '#') {
                house_matrix[i][j] = -1;
            } else if (cell >= '1' && cell <= '9') {
                house_matrix[i][j] = cell - '0';
            } else if (cell == 'D') {
                docking_station = {i, j};
                house_matrix[i][j] = 20;
            } else {
                house_matrix[i][j] = 0;
            }
        }
    }
}

void House::findDockingStation() {
    bool found = false;
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < width; ++j) {
            if (house_matrix[i][j] == 20) {
                docking_station = {i, j};
                found = true;
                break;
            }
        }
        if (found) break;
    }
    if (!found) {
        throw std::runtime_error("Docking station 'D' not found in file");
    }
}
bool House::Wall_cell(int i, int j) const {
    return getHouseMatrix()[i][j]==-1;
}
bool House::legeal_cell(int i,int j) const {
    return (j<width&&i<length);
}

