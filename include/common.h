#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>



// Constants
constexpr double CLUSTER_DISTANCE_THRESHOLD = 2.0;  //2 meters
constexpr double TRACKING_DISTANCE_THRESHOLD = 3.0;  //3 meters for tracking objects


// Helper functions to calculate distance between two points
inline double calculateDistance(double x1, double y1, double x2, double y2){
    return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
}

//Generate a random ID for a fused objects
inline int generateRandomId(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1, 10000);
    return dis(gen);
}


#endif // COMMON_H