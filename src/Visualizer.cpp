#include "Visualizer.h"
#include <iostream>
#include <fstream>

void Visualizer::printConsole(const Grid& grid, int preyCount, int predatorCount) {
    for (int y = 0; y < grid.getHeight(); y++) {
        for (int x = 0; x < grid.getWidth(); x++) {
            EntityType type = grid.get(x, y);
            if (type == EntityType::Empty) std::cout << ". ";
            else if (type == EntityType::Prey) std::cout << "o ";
            else std::cout << "X ";
        }
        std::cout << "\n";
    }
    std::cout << "Prey: " << preyCount << " | Predators: " << predatorCount << "\n\n";
}

void Visualizer::savePPM(const Grid& grid, const std::string& filename) {
    std::ofstream file(filename);
    file << "P3\n" << grid.getWidth() << " " << grid.getHeight() << "\n255\n";
    
    for (int y = 0; y < grid.getHeight(); y++) {
        for (int x = 0; x < grid.getWidth(); x++) {
            EntityType type = grid.get(x, y);
            if (type == EntityType::Empty) {
                file << "0 0 0 ";
            } else if (type == EntityType::Prey) {
                file << "0 255 0 ";
            } else {
                file << "255 0 0 ";
            }
        }
        file << "\n";
    }
}