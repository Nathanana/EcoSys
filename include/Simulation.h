#pragma once

#include <random>
#include "Grid.h"
#include "Parameters.h"

class Simulation {
private:
    Grid grid;
    Grid nextGrid;
    Parameters params;
    
    int preyCount, predatorCount;
    
    std::mt19937 rng;
    std::uniform_real_distribution<double> dist;
    
    void processCell(int x, int y);
    void processPrey(int x, int y);
    void processPredator(int x, int y);
    
    std::pair<int, int> getRandomNeighbor(const std::vector<std::pair<int, int>>& neighbors);
    std::pair<int, int> findEmptyNeighbor(int x, int y);
    std::pair<int, int> findPreyNeighbor(int x, int y);

public:
    Simulation(int width, int height, int initialPrey, int initialPredators);
    
    void step();
    
    const Grid& getGrid() const { return grid; }
    int getPreyCount() const { return preyCount; }
    int getPredatorCount() const { return predatorCount; }
};