#include "fusion.h"
#include "common.h"
#include "parser.h"
#include "clustering.h"
#include "kalman_filter.h"
#include "data_types.h"


void fuseSensorData(const std::string& sensorFile, const std::string& imuFile, const std::string& outputFile) {

    // Parse input files
    std::vector<Detection> detections = parseSensorData(sensorFile);
    std::vector<IMUData> imuData = parseIMUData(imuFile);

    if (detections.empty() || imuData.empty()) {
        std::cerr << "Error: No data to process" << std::endl;
        return;
    }

    // Initialize Kalman filter for heading
    KalmanFilter kalmanFilter;

    // Open output file
    std::ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        std::cerr << "Error opening outout file:" << outputFile << std::endl;
        return;
    }

    // Write header
    outFile << "f_timestamp, f_id, cluster_data,, heading, status" << std::endl;

    // Process data sequentially by timestamp
    size_t imuIndex = 0;
    std::vector<Detection> currentDetections;
    std::vector<Cluster> previousClusters;

    // Get all unique timestamps from detections
    std::vector<Timestamp> uniqueTimestamps;
    for (const auto& detection : detections) {
        if (uniqueTimestamps.empty() || !(uniqueTimestamps.back() == detection.timestamp)) {
            uniqueTimestamps.push_back(detection.timestamp);
        }
    }

    // Process each timestamp
    for (const auto& timestamp : uniqueTimestamps) {

        // Collect all detections at this timestamp
        currentDetections.clear();
        for (const auto& detection : detections) {
            if (detection.timestamp == timestamp) {
                currentDetections.push_back(detection);
            }
        }

        // Find corresponding IMU data(closest in time)
        while (imuIndex < imuData.size() - 1 && 
                !(imuData[imuIndex].timestamp == timestamp) && 
                imuData[imuIndex + 1].timestamp < timestamp) {
            imuIndex++;
        }

        // Get IMU data
        double headingAngle = imuData[imuIndex].heading;
        std::string status = imuData[imuIndex].state;

        // Apply Kalman filter to heading
        double filteredHeading = kalmanFilter.update(headingAngle);

        // Cluster detections at this timestamp
        std::vector<Cluster> currentClusters =clusterDetections(currentDetections, CLUSTER_DISTANCE_THRESHOLD);

        // Assign IDs to cluster (tracking objects over time)
        for (auto& cluster : currentClusters) {
            // Try to find a matching cljuster from previous timestamp
            int closestIndex = findClosestCluster(cluster, previousClusters, TRACKING_DISTANCE_THRESHOLD);

            if (closestIndex >= 0 && previousClusters[closestIndex].fusedId != 0) {

                // Use same ID as previous matching cluster
                cluster.fusedId = previousClusters[closestIndex].fusedId;
            }

            else {
                // Generate a new random ID
                cluster.fusedId = generateRandomId();
            }

            // Write to output file
            outFile << timestamp.toString() << ","
                    << cluster.fusedId << ","
                    << formatClusterData(cluster.clusterData) << ","
                    << filteredHeading << ","
                    << status << std::endl;
        }

        // Save current clusters for next iteration
        previousClusters = currentClusters;

    }

    outFile.close();
    std::cout << "Data Fusion complete. Results saved to " << outputFile << std::endl;

}
