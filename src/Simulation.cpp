#include "Simulation.h"

Simulation::Simulation(int w, int h, int initialPrey, int initialPredators)
    : grid(w, h), nextGrid(w, h), preyCount(0), predatorCount(0),
      rng(std::random_device{}()), dist(0.0, 1.0) {
    
    // Place initial prey
    for (int i = 0; i < initialPrey; i++) {
        int x, y;
        do {
            x = rng() % w;
            y = rng() % h;
        } while (grid.get(x, y) != EntityType::Empty);
        grid.set(x, y, EntityType::Prey);
        preyCount++;
    }
    
    // Place initial predators
    for (int i = 0; i < initialPredators; i++) {
        int x, y;
        do {
            x = rng() % w;
            y = rng() % h;
        } while (grid.get(x, y) != EntityType::Empty);
        grid.set(x, y, EntityType::Predator);
        predatorCount++;
    }
}

void Simulation::step() {
    nextGrid = grid;
    
    for (int y = 0; y < grid.getHeight(); y++) {
        for (int x = 0; x < grid.getWidth(); x++) {
            processCell(x, y);
        }
    }
    
    grid = nextGrid;
}

void Simulation::processCell(int x, int y) {
    EntityType type = grid.get(x, y);
    if (type == EntityType::Prey) {
        processPrey(x, y);
    } else if (type == EntityType::Predator) {
        processPredator(x, y);
    }
}

void Simulation::processPrey(int x, int y) {
    // Reproduction
    if (dist(rng) < params.preyBirthRate) {
        auto empty = findEmptyNeighbor(x, y);
        if (empty.first != -1) {
            nextGrid.set(empty.first, empty.second, EntityType::Prey);
            preyCount++;
        }
    }
    
    // Movement
    if (dist(rng) < params.preyMovementRate) {
        auto neighbors = grid.getNeighbors(x, y);
        auto neighbor = getRandomNeighbor(neighbors);
        if (neighbor.first != -1 && grid.get(neighbor.first, neighbor.second) == EntityType::Empty) {
            nextGrid.set(x, y, EntityType::Empty);
            nextGrid.set(neighbor.first, neighbor.second, EntityType::Prey);
        }
    }
}

void Simulation::processPredator(int x, int y) {
    // Death
    if (dist(rng) < params.predatorDeathRate) {
        nextGrid.set(x, y, EntityType::Empty);
        predatorCount--;
        return;
    }
    
    // Hunt prey
    auto prey = findPreyNeighbor(x, y);
    if (prey.first != -1 && dist(rng) < params.predationRate) {
        nextGrid.set(x, y, EntityType::Empty);
        nextGrid.set(prey.first, prey.second, EntityType::Predator);
        preyCount--;
        
        // Reproduction from eating
        if (dist(rng) < params.predatorBirthRate) {
            auto empty = findEmptyNeighbor(x, y);
            if (empty.first != -1) {
                nextGrid.set(empty.first, empty.second, EntityType::Predator);
                predatorCount++;
            }
        }
    }
    // Random movement
    else if (dist(rng) < params.predatorMovementRate) {
        auto neighbors = grid.getNeighbors(x, y);
        auto neighbor = getRandomNeighbor(neighbors);
        if (neighbor.first != -1 && grid.get(neighbor.first, neighbor.second) == EntityType::Empty) {
            nextGrid.set(x, y, EntityType::Empty);
            nextGrid.set(neighbor.first, neighbor.second, EntityType::Predator);
        }
    }
}

std::pair<int, int> Simulation::getRandomNeighbor(const std::vector<std::pair<int, int>>& neighbors) {
    if (neighbors.empty()) return {-1, -1};
    return neighbors[rng() % neighbors.size()];
}

std::pair<int, int> Simulation::findEmptyNeighbor(int x, int y) {
    auto neighbors = grid.getNeighbors(x, y);
    std::vector<std::pair<int, int>> empty;
    for (auto [nx, ny] : neighbors) {
        if (nextGrid.get(nx, ny) == EntityType::Empty) {
            empty.push_back({nx, ny});
        }
    }
    return getRandomNeighbor(empty);
}

std::pair<int, int> Simulation::findPreyNeighbor(int x, int y) {
    auto neighbors = grid.getNeighbors(x, y);
    std::vector<std::pair<int, int>> prey;
    for (auto [nx, ny] : neighbors) {
        if (grid.get(nx, ny) == EntityType::Prey) {
            prey.push_back({nx, ny});
        }
    }
    return getRandomNeighbor(prey);
}