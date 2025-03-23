#ifndef FUSION_H
#define FUSION_H

#include <string>

// Main function to proces and fuse sensor and IMU data

void fuseSensorData(const std:: string& sensorFile, const std::string& imuFile, const std::string& outputFile);

#endif // FUSION_H