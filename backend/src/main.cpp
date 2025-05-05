#include <crow.h>
#include <iostream>
#include <cmath>
#include <random>
#include "../include/monteCarlo.h"


int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        std::ifstream file("../frontend/index.html"); // Open the index.html file
        if (!file.is_open()) {
            return crow::response(404, "File not found"); // Handle the case where the file doesn't exist
        }
        std::stringstream buffer;
        buffer << file.rdbuf(); // Read the entire file content into a stringstream
        return crow::response(buffer.str()); // Return the file content as the response
    });


    CROW_ROUTE(app, "/pricing").methods(crow::HTTPMethod::POST)(
        [](const crow::request& req)
        {
            crow::json::rvalue input_json;
        try {
            input_json = crow::json::load(req.body);
            if (!input_json) {
                return crow::response(crow::BAD_REQUEST, "Invalid JSON");
            }
            double S0_ = input_json["initialStockPrice"].d();
            double K = 100.0; // Strike Price
            double r = 0.05; // Risk free rate
            double v = 0.2; // Volatility
            double T = 1; // DTE (years)
            int numSimulations = 1000000; // Number of simulations to run

            double callPrice = monteCarloPricing(S0_, K, r, v, T, numSimulations, true);
            double putPrice = monteCarloPricing(S0_, K, r, v, T, numSimulations, false);

            crow::json::wvalue response_json;
            response_json["callPrice"] = callPrice;
            response_json["putPrice"] = putPrice;

            return crow::response(crow::OK, response_json);
        
        } catch (const std::exception& e) {
            return crow::response(crow::INTERNAL_SERVER_ERROR, std::string("Exception: ") + e.what());
        } catch (...) {
            return crow::response(crow::INTERNAL_SERVER_ERROR, "Unknown Server Error");
        }
        }
    );

    app.port(8000).multithreaded().run();
    return 0;
}