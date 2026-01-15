#include "Simulation.h"
#include <iostream>
#include <cassert>

void test_simulation_initialization() {
    Simulation sim(10, 10, 5, 2);
    
    assert(sim.getPreyCount() == 5);
    assert(sim.getPredatorCount() == 2);
    
    std::cout << "Simulation initialization test passed\n";
}

void test_simulation_grid_size() {
    Simulation sim(20, 15, 10, 5);
    
    assert(sim.getGrid().getWidth() == 20);
    assert(sim.getGrid().getHeight() == 15);
    
    std::cout << "Simulation grid size test passed\n";
}

void test_simulation_step() {
    Simulation sim(10, 10, 10, 5);
    
    int initialPrey = sim.getPreyCount();
    int initialPredators = sim.getPredatorCount();

    for (int i = 0; i < 10; i++) {
        sim.step();
    }

    assert(sim.getPreyCount() >= 0);
    assert(sim.getPredatorCount() >= 0);
    
    std::cout << "Simulation step test passed\n";
}

void test_simulation_populations() {
    Simulation sim(5, 5, 25, 0); // Fill grid with prey
    
    // With no predators, prey should survive
    for (int i = 0; i < 5; i++) {
        sim.step();
    }
    
    assert(sim.getPreyCount() > 0);
    assert(sim.getPredatorCount() == 0);
    
    std::cout << "Simulation populations test passed\n";
}

int main() {
    test_simulation_initialization();
    test_simulation_grid_size();
    test_simulation_step();
    test_simulation_populations();
    std::cout << "All Simulation tests passed!\n";
    return 0;
}