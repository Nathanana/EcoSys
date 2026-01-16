#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "Simulation.h"
#include "Visualizer.h"
#include "DataLogger.h"

int main() {
    // Configuration
    const int WIDTH = 50;
    const int HEIGHT = 50;
    const int INITIAL_PREY = 300;
    const int INITIAL_PREDATORS = 50;
    const int STEPS = 500;
    const int DISPLAY_INTERVAL = 10;
    
    // Initialize simulation
    Simulation sim(WIDTH, HEIGHT, INITIAL_PREY, INITIAL_PREDATORS);
    DataLogger logger("population_data.csv");
    
    // Run simulation
    for (int i = 0; i < STEPS; i++) {
        // Display and save
        if (i % DISPLAY_INTERVAL == 0) {
            std::cout << "Step " << i << ":\n";
            Visualizer::printConsole(sim.getGrid(), sim.getPreyCount(), sim.getPredatorCount());
            
            std::ostringstream filename;
            filename << "frame_" << std::setw(4) << std::setfill('0') << i << ".ppm";
            Visualizer::savePPM(sim.getGrid(), filename.str());
        }
        
        // Log data
        logger.log(i, sim.getPreyCount(), sim.getPredatorCount());
        
        // Step simulation
        sim.step();
        
        // Check extinction
        if (sim.getPreyCount() == 0 || sim.getPredatorCount() == 0) {
            std::cout << "Population extinct at step " << i << "\n";
            break;
        }
    }
    
    std::cout << "Simulation complete!\n";
    return 0;
}