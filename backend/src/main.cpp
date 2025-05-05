#include <crow.h>
#include <iostream>
#include <cmath>
#include <random>
#include "../include/monteCarlo.h"


int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")(
        []()
        {
            double S0 = 150.0; // Initial Stock Price
            double K = 100.0; // Strike Price
            double r = 0.05; // Risk free rate
            double v = 0.2; // Volatility
            double T = 1; // DTE (years)
            int numSimulations = 1000000; // Number of simulations to run


            double callPrice = monteCarloPricing(S0, K, r, v, T, numSimulations, true);
            double putPrice = monteCarloPricing(S0, K, r, v, T, numSimulations, false);

            std::stringstream ss;
            ss << std::fixed << std::setprecision(4) << "Hardcoded EU Call ($" << callPrice;
            ss << std::fixed << std::setprecision(4) << "Hardcoded EU Put ($" << putPrice;

            return crow::response(200, ss.str());
        }
    );

    app.port(8000).run();
    return 0;
}