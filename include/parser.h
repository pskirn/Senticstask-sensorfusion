#ifndef PARSER_H
#define PARSER_H

#include "data_types.h"
#include <string>
#include <vector>

// Parse sensor data from a JSON file
std::vector<Detection> parseSensorData(const std::string& filename);

// Parse IMU data from a CSV file
std::vector<IMUData> parseIMUData(const std::string& filename);

// Format cluster data as a string for CSV Output
std::string formatClusterData(const std::vector<std::vector<double>>& clusterData);

#endif // PARSER_H