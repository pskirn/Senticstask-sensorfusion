#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include "timestamp.h"
#include <string>
#include <vector>

// Structure for sensor detection
struct Detection {
    Timestamp timestamp;
    std::string sensorId;
    int objectId;
    double x, y;
    std::string objectClass;

    Detection() : objectId(0), x(0), y(0) {}
};

// Structure for IMU data
struct IMUData {
    Timestamp timestamp;
    double heading;
    std::string state;
    double acceleration;

    IMUData() : heading(0), acceleration(0) {}
};

//Structure for clustered data
struct Cluster {
    Timestamp timestamp;
    int fusedId;
    std::vector<std::vector<double>> clusterData; // x, y, sensorId

    Cluster(): fusedId(0) {}
};


#endif // DATA_TYPES_H