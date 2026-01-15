#include "Grid.h"

Grid::Grid(int w, int h) : width(w), height(h) {
    cells.resize(height, std::vector<EntityType>(width, EntityType::Empty));
}

EntityType Grid::get(int x, int y) const {
    return cells[y][x];
}

void Grid::set(int x, int y, EntityType type) {
    cells[y][x] = type;
}

bool Grid::isValid(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

std::vector<std::pair<int, int>> Grid::getNeighbors(int x, int y) const {
    std::vector<std::pair<int, int>> neighbors;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx, ny = y + dy;
            if (isValid(nx, ny)) {
                neighbors.push_back({nx, ny});
            }
        }
    }
    return neighbors;
}