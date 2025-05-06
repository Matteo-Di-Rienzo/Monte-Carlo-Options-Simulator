#include <iostream>
#include <cmath>
#include <random>


// Goal here is to create monte carlo pricing in CPP, need helper functions as well as main method with the parameters.

// Continuous equation is dS_t = uS_t dt + sigmaS_t dW
// Drift term: (r - 1/2 o^2)


// First we have to generate random values that follow a normal distribution, these values will help predict the call or put's price.
// This function will generate the Z value.

double generateZValue(double mean, double stddev) {
    static std::mt19937 generator(std::random_device{}());
    std::normal_distribution<double> distribution(mean, stddev);
    return distribution(generator);
}

double callPayoff(double S, double K) {
    return std::max(0.0, S - K);
}

double putPayoff(double S, double K) {
    return std::max(0.0, K - S);
}

// Take avg of all the runs using Z values, to get the price of the option

double monteCarloPricing(double S0, double K, double r, double v, double T, int numSimulations, bool isCallOption) {
    double optionTotalPayoff = 0.0;

    for (int i = 0; i < numSimulations; i++) {

        double ST = S0 * exp((r - 0.5 * v*v) * T + v * sqrt(T) * generateZValue(0.0, 1.0));

        if (isCallOption) {
            double optionPayoff = callPayoff(ST, K);
            optionTotalPayoff += optionPayoff;
        }
        else {
            double optionPayoff = putPayoff(ST, K);
            optionTotalPayoff += optionPayoff;
        }

    }

    double averagePayoff = optionTotalPayoff / static_cast<double>(numSimulations);

    // Now discount by the risk free rate

    averagePayoff = std::exp((- r) * T) * averagePayoff;

    return averagePayoff;
}