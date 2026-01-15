#include "DataLogger.h"
#include <iostream>
#include <fstream>
#include <cassert>

void test_data_logger_creation() {
    {
        DataLogger logger("test_output.csv");
        logger.log(0, 100, 50);
        logger.log(1, 105, 48);
        logger.log(2, 110, 46);
    }
    
    // Check file exists and has content
    std::ifstream file("test_output.csv");
    assert(file.is_open());
    
    std::string line;
    std::getline(file, line);
    assert(line == "Step,Prey,Predators");
    
    std::getline(file, line);
    assert(line == "0,100,50");
    
    std::getline(file, line);
    assert(line == "1,105,48");
    
    file.close();
    
    std::cout << "DataLogger creation and logging test passed\n";
}

void test_data_logger_multiple_logs() {
    {
        DataLogger logger("test_multiple.csv");
        for (int i = 0; i < 100; i++) {
            logger.log(i, 100 + i, 50 - i/2);
        }
    }
    
    std::ifstream file("test_multiple.csv");
    assert(file.is_open());
    
    int lineCount = 0;
    std::string line;
    while (std::getline(file, line)) {
        lineCount++;
    }
    
    assert(lineCount == 101); // Header + 100 data lines
    file.close();
    
    std::cout << "DataLogger multiple logs test passed\n";
}

int main() {
    test_data_logger_creation();
    test_data_logger_multiple_logs();
    std::cout << "All DataLogger tests passed!\n";
    return 0;
}
