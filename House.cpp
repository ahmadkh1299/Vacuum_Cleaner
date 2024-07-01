#include "House.h"

House::House()
        : docking_station(-1, -1), width(0), length(0) {}

House::House(const std::vector<std::string>& layout_v)
        : docking_station(-1, -1), width(0), length(0),total_dirt(0) {
    std::vector<std::string> layout_copy = layout_v;
    addWallsPadding(layout_copy);
    initializeMatrix(layout_copy);
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
                total_dirt+=house_matrix[i][j];
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

void House::addWallsPadding(std::vector<std::string>& layout_v) {
    int max_length = 0;

    for (const auto& row : layout_v) {
        if (row.size() > max_length) {
            max_length = row.size();
        }
    }

    for (auto& row : layout_v) {
        while (row.size() < max_length) {
            row.push_back('#');
        }
    }

    bool needs_walls = false;

    // Check top and bottom rows
    for (char c : layout_v[0]) {
        if (c != '#') {
            needs_walls = true;
            break;
        }
    }
    for (char c : layout_v[layout_v.size() - 1]) {
        if (c != '#') {
            needs_walls = true;
            break;
        }
    }

    // Check left and right columns
    if (!needs_walls) {
        for (const auto& row : layout_v) {
            if (row[0] != '#' || row[max_length - 1] != '#') {
                needs_walls = true;
                break;
            }
        }
    }

    if (needs_walls) {
        for (auto& row : layout_v) {
            row.insert(row.begin(), '#');
            row.push_back('#');
        }
        std::string wall_row(max_length + 2, '#');
        layout_v.insert(layout_v.begin(), wall_row);
        layout_v.push_back(wall_row);
    }
}

std::vector<std::vector<int>>& House::getHouseMatrix() {
    return house_matrix;
}

std::pair<int, int> House::getDockingStation() const {
    return docking_station;
}

int House::getWidth() const {
    return width;
}

int House::getLength() const {
    return length;
}
int House::gettotaldirt() const {
    return total_dirt;
}
void House::decreaseTotaldirt() {
    total_dirt--;
}
