#ifndef CLUSTERING_H
#define CLUSTERING_H

#include  "data_types.h"
#include <vector>

// Cluster detections based that occur at the same timestamp
std::vector<Cluster> clusterDetections(const std::vector<Detection>& detections, double distancethreshold);

// Find the closest previous cluster for tracking
int findClosestCluster(const Cluster& current, const std::vector<Cluster>& prevClusters, double maxDistance);

#endif // CLUSTERING_H