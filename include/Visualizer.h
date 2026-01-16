#pragma once

#include <string>
#include "Grid.h"

class Visualizer {
public:
    static void printConsole(const Grid& grid, int preyCount, int predatorCount);
    static void savePPM(const Grid& grid, const std::string& filename);
};