#include "DataLogger.h"

DataLogger::DataLogger(const std::string& filename) {
    file.open(filename);
    file << "Step,Prey,Predators\n";
}

DataLogger::~DataLogger() {
    if (file.is_open()) {
        file.close();
    }
}

void DataLogger::log(int step, int preyCount, int predatorCount) {
    file << step << "," << preyCount << "," << predatorCount << "\n";
}