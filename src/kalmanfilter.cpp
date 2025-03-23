#include "kalman_filter.h"

KalmanFilter::KalmanFilter(double processNoise, double measurementNoise)
    : x(0), P(1), Q(processNoise), R(measurementNoise), initialized(false) {
}

double KalmanFilter::update(double measurement) {
    if (!initialized) {
        x = measurement;
        initialized = true;
        return x;
    }

    // Prediction step
    // State prediction
    // Covaariance prediction
    P = P + Q;


    //Update step
    //kalman gain
    double K = P / (P + R);

    //State update
    x = x + K * (measurement - x);

    // Covariance update
    P = (1 - K) * P;

    return x;
}