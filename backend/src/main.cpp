#include <crow.h>
#include <iostream>
#include <cmath>
#include <random>
#include "../include/monteCarlo.h"
#include <fstream>
#include <sstream>


std::string readFile(const std::string& path) {
    std::ifstream file(path);
        if (!file) {
            return "Error reading file";
        }
        std::ostringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
}
        

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        auto html = readFile("../frontend/index.html");
        return crow::response(html);
    });

    
    CROW_ROUTE(app, "/js/<path>")([](const std::string& fname){
        auto content = readFile("../frontend/js/" + fname);
        crow::response res(content);
        res.set_header("Content-Type", "application/javascript");
        return res;
      });

    CROW_ROUTE(app, "/css/<path>")([](const std::string& fname){
        auto content = readFile("../frontend/css/" + fname);
        crow::response res(content);
        res.set_header("Content-Type", "application/css");
        return res;
    });


    CROW_ROUTE(app, "/pricing").methods(crow::HTTPMethod::POST)([](const crow::request& req)
        {
            crow::json::rvalue input_json;
        try {
            input_json = crow::json::load(req.body);
            if (!input_json) {
                return crow::response(crow::BAD_REQUEST, "Invalid JSON");
            }
            double S0_ = input_json["initialStockPrice"].d();
            double K_ = input_json["strikePrice"].d();
            double r_ = input_json["riskFreeRate"].d();
            double v = input_json["volatility"].d();
            double T = input_json["dte"].d();
            int numSimulations = input_json["numSimulations"].d();

            double callPrice = monteCarloPricing(S0_, K_, r_, v, T, numSimulations, true);
            double putPrice = monteCarloPricing(S0_, K_, r_, v, T, numSimulations, false);

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