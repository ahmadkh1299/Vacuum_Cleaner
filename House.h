#ifndef HOUSE_H
#define HOUSE_H

#include <vector>
#include <string>
#include <stdexcept>

class House {
public:
    House();
    explicit House(const std::vector<std::string>& layout_v);

    void initializeMatrix(const std::vector<std::string>& layout_v);
    void findDockingStation();
    void addWallsPadding(std::vector<std::string>& layout_v);

    const std::vector<std::vector<int>>& getHouseMatrix() const {
        return house_matrix;
    }

    std::pair<int, int> getDockingStation() const {
        return docking_station;
    }

    int getWidth() const {
        return width;
    }

    int getLength() const {
        return length;
    }

    bool Wall_cell(int i,int j) const;
    bool legeal_cell(int x,int y) const;

private:
    std::vector<std::vector<int>> house_matrix;
    std::pair<int, int> docking_station;
    int width;
    int length;
};

#endif // HOUSE_H
