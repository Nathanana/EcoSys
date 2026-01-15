#pragma once

#include <string>
#include <fstream>

class DataLogger {
private:
    std::ofstream file;

public:
    DataLogger(const std::string& filename);
    ~DataLogger();
    
    void log(int step, int preyCount, int predatorCount);
};