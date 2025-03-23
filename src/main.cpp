#include "fusion.h"
#include <iostream>
#include <chrono>

int main(int argc, char* argv[]) {

    // Check command line arguments
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <sensor_data.json> <imu_data.csv> <output.csv>" << std::endl;
            return 1;
    }

    std::string sensorFile = argv[1];
    std::string imuFile = argv[2];
    std::string outputFile = argv[3];

    // Measure execution time
    auto start = std::chrono::high_resolution_clock::now();

    // Process and fuse data
    fuseSensorData(sensorFile, imuFile, outputFile);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Execution time: " << elapsed.count() << "seconds" << std::endl;

    return 0;
}