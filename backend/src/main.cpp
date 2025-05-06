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
        auto content = readFile("../frontend/index.html");
        return crow::response(content);
    });

    
    CROW_ROUTE(app, "/js/<path>")([](const std::string& fileName){
        auto content = readFile("../frontend/js/" + fileName);
        crow::response res(content);
        res.set_header("Content-Type", "application/javascript");
        return res;
      });

    CROW_ROUTE(app, "/css/<path>")([](const std::string& fileName){
        auto content = readFile("../frontend/css/" + fileName);
        crow::response res(content);
        res.set_header("Content-Type", "text/css");
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
            double v_ = input_json["volatility"].d();
            double T_ = input_json["dte"].d();
            int numSimulations_ = input_json["numSimulations"].d();

            double callPrice = monteCarloPricing(S0_, K_, r_, v_, T_, numSimulations_, true);
            double putPrice = monteCarloPricing(S0_, K_, r_, v_, T_, numSimulations_, false);

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