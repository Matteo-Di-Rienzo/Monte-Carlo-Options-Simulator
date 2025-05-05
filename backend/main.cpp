#include <iostream>
#include <cmath>
#include <random>
#include "./include/monteCarlo.h"




int main() {
    // Params
    double S0 = 150.0; // Initial Stock Price
    double K = 100.0; // Strike Price
    double r = 0.05; // Risk free rate
    double v = 0.2; // Volatility
    double T = 1; // DTE (years)
    int numSimulations = 1000000; // Number of simulations to run

    double callPrice = monteCarloPricing(S0, K, r, v, T, numSimulations, true);
    double putPrice = monteCarloPricing(S0, K, r, v, T, numSimulations, false);

    std::cout << "EU Call Option Price: " << callPrice << std::endl;
    std::cout << "EU Put Option Price: " << putPrice << std::endl;
}