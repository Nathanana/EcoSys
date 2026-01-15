#include "Grid.h"
#include <iostream>
#include <cassert>

void test_grid_initialization() {
    Grid grid(10, 10);
    assert(grid.getWidth() == 10);
    assert(grid.getHeight() == 10);
    
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            assert(grid.get(x, y) == EntityType::Empty);
        }
    }
    std::cout << "✓ Grid initialization test passed\n";
}

void test_grid_set_get() {
    Grid grid(5, 5);
    grid.set(2, 3, EntityType::Prey);
    assert(grid.get(2, 3) == EntityType::Prey);
    
    grid.set(4, 1, EntityType::Predator);
    assert(grid.get(4, 1) == EntityType::Predator);
    
    std::cout << "✓ Grid set/get test passed\n";
}

void test_grid_validity() {
    Grid grid(10, 10);
    assert(grid.isValid(0, 0) == true);
    assert(grid.isValid(9, 9) == true);
    assert(grid.isValid(-1, 0) == false);
    assert(grid.isValid(0, -1) == false);
    assert(grid.isValid(10, 0) == false);
    assert(grid.isValid(0, 10) == false);
    
    std::cout << "✓ Grid validity test passed\n";
}

void test_grid_neighbors() {
    Grid grid(5, 5);
    
    // Corner cell (0,0) should have 3 neighbors
    auto neighbors = grid.getNeighbors(0, 0);
    assert(neighbors.size() == 3);
    
    // Edge cell (2,0) should have 5 neighbors
    neighbors = grid.getNeighbors(2, 0);
    assert(neighbors.size() == 5);
    
    // Center cell (2,2) should have 8 neighbors
    neighbors = grid.getNeighbors(2, 2);
    assert(neighbors.size() == 8);
    
    std::cout << "Grid neighbors test passed\n";
}

int main() {
    test_grid_initialization();
    test_grid_set_get();
    test_grid_validity();
    test_grid_neighbors();
    std::cout << "All Grid tests passed!\n";
    return 0;
}