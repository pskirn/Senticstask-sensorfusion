#include "parser.h"
#include "common.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::vector<Detection> parseSensorData(const std::string& filename) {
    std::vector<Detection> detections;
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening sensor data file: " << filename << std::endl;
        return detections;
    }
    
    json sensorData;
    file >> sensorData;
    
    // Loop through each camera entry
    for (auto it = sensorData.begin(); it != sensorData.end(); ++it) {
        std::string sensorId = it.key(); // This is the camera ID (e.g., "cam_51")
        const auto& cameraData = it.value();
        
        std::string timestampStr = cameraData["timestamp"];
        Timestamp timestamp(timestampStr);
        
        // Parse objects detected by this sensor
        const auto& objectClasses = cameraData["object_classes"];
        const auto& objectIds = cameraData["object_ids"];
        const auto& positions = cameraData["object_positions_x_y"];
        
        for (size_t i = 0; i < objectIds.size(); ++i) {
            Detection detection;
            detection.timestamp = timestamp;
            detection.sensorId = sensorId;
            detection.objectId = objectIds[i];
            detection.objectClass = objectClasses[i];
            
            const auto& positionArray = positions[i];
            detection.x = positionArray[0];
            detection.y = positionArray[1];
            
            detections.push_back(detection);
        }
    }
    
    // Sort detections by timestamp
    std::sort(detections.begin(), detections.end(), 
              [](const Detection& a, const Detection& b) {
                  return a.timestamp < b.timestamp;
              });
    
    return detections;
}

std::vector<IMUData> parseIMUData(const std::string& filename) {
    std::vector<IMUData> imuData;
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening IMU data file: " << filename << std::endl;
        return imuData;
    }
    
    std::string line;
    // Skip header
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        
        IMUData data;
        
        // Parse timestamp
        std::getline(ss, cell, ',');
        data.timestamp = Timestamp(cell);
        
        // Parse heading
        std::getline(ss, cell, ',');
        data.heading = std::stod(cell);
        
        // Parse state
        std::getline(ss, cell, ',');
        data.state = cell;
        
        // Parse acceleration
        std::getline(ss, cell, ',');
        data.acceleration = std::stod(cell);
        
        imuData.push_back(data);
    }
    
    // Sort IMU data by timestamp
    std::sort(imuData.begin(), imuData.end(), 
              [](const IMUData& a, const IMUData& b) {
                  return a.timestamp < b.timestamp;
              });
    
    return imuData;
}

std::string formatClusterData(const std::vector<std::vector<double>>& clusterData) {
    std::stringstream ss;
    ss << "[";
    for (size_t i = 0; i < clusterData.size(); ++i) {
        ss << "[" << clusterData[i][0] << "," << clusterData[i][1] << "," << clusterData[i][2] << "]";
        if (i < clusterData.size() - 1) {
            ss << ",";
        }
    }
    ss << "]";
    return ss.str();
}