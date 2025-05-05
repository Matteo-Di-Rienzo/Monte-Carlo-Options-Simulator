

double generateZValue(double mean, double stddev);
double callPayoff(double S, double K);
double putPayoff(double S, double K);
double monteCarloPricing(double S0, double K, double r, double v, double T, int numSimulations, bool isCallOption);