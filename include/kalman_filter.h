#ifndef KALMAN_FILTER_H
#define KALMAN_FILTER_H

class KalmanFilter {
    private:

        // State vector
        double x;

        // Uncertainty
        double P;

        //Process noise
        double Q;

        // Measurement noise
        double R;

        bool initialized;

    public:

        // Constructor
        KalmanFilter(double processNoise = 0.1, double measurementNoise = 0.1);

        // Update the filter with a new measurement
        double update(double measurement);    
};

#endif // KALMAN_FILTER_H