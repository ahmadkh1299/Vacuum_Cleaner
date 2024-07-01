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

    std::vector<std::vector<int>>& getHouseMatrix(); // Removed const
    std::pair<int, int> getDockingStation() const;
    int getWidth() const;
    int getLength() const;
    int gettotaldirt() const;
    void decreaseTotaldirt();

private:
    std::vector<std::vector<int>> house_matrix;
    std::pair<int, int> docking_station;
    int width;
    int length;
    int total_dirt;
};

#endif // HOUSE_H