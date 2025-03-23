#include "clustering.h"
#include "common.h"

std::vector<Cluster> clusterDetections(const std::vector<Detection>& detections, double distanceThreshold) { 
    std::vector<Cluster> clusters;
    std::vector<bool> processed(detections.size(), false);

    for (size_t i = 0; i< detections.size(); ++i) {
        if (processed[i]) continue;

        // Start a new cluster
        Cluster cluster;
        cluster.timestamp = detections[i].timestamp;

        // Add the first detection to the cluster
        std::vector<double> data = {detections[i].x, detections[i].y, std::stod(detections[i].sensorId.substr(4))};
        cluster.clusterData.push_back(data);
        processed[i] = true;

        // Find all nearby detections within threshold
        for (size_t j = 0; j < detections.size(); ++j) {
            if (i ==j || processed[j]) continue;

            // Only cluster detections with the same timestamp
            if (!(detections[i].timestamp == detections[j].timestamp)) continue;

            double distance = calculateDistance(detections[i].x, detections[i].y, detections[j].x, detections[j].y);
            if (distance <= distanceThreshold) {

                // Add detection to the cluster
                std::vector<double> data = {detections[j].x, detections[j].y, std::stod(detections[j].sensorId.substr(4)) };
                cluster.clusterData.push_back(data);
                processed[j] = true;
            }
        }

        // Only add non-empty clusters
        if (!cluster.clusterData.empty()) { clusters.push_back(cluster);
        }
    }

    return clusters;

}

int findClosestCluster(const Cluster& current, const std::vector<Cluster>& prevClusters, double maxDistance) {
    double minDistance = maxDistance;
    int closestIndex = -1;

    // clculate average position of current cluster
    double avgX = 0, avgY = 0;
    for (const auto& data : current.clusterData) {
        avgX += data[0];
        avgY += data[1];
    } 

    avgX /= current.clusterData.size();
    avgY /= current.clusterData.size();

    // Find closest previous cluster
    for (size_t i = 0; i < prevClusters.size(); ++i) {

        // Calculate average position of previous cluster
        double prevAvgX = 0, prevAvgY = 0;
        for (const auto& data : prevClusters[i].clusterData) {
            prevAvgX += data[0];
            prevAvgY += data[1];
        }

        prevAvgX /= prevClusters[i].clusterData.size();
        prevAvgY /= prevClusters[i].clusterData.size();

        // Calculate distance between cluster centers
        double distance = calculateDistance(avgX, avgY, prevAvgX, prevAvgY);
        
        if (distance < minDistance) {
            minDistance = distance;
            closestIndex = i;
        }
    }

    return closestIndex;
}