# Monte Carlo Options Simulator

## Project Description

This project is a full-stack web application designed to simulate and visualize the pricing of European call and put options using the Monte Carlo method. Leveraging the discretized Geometric Brownian Motion model, the application provides users with an interactive platform to input key financial parameters and observe how option prices evolve over the time to expiration.

Developed as a demonstration of full-stack web development principles and computational finance techniques, this project integrates a high-performance C++ backend for the computationally intensive Monte Carlo simulations with a dynamic frontend built using HTML, CSS, and JavaScript for user interaction and data visualization. The Crow C++ microframework is utilized to handle backend routing and serve the frontend assets.

## Technologies Used

* **Backend:**
    * C++: Core simulation logic and backend application.
    * Crow: Lightweight C++ framework for full stack applications.
* **Frontend:**
    * HTML: Structure of the web pages.
    * CSS: Styling and layout.
    * JavaScript: Frontend logic, user interaction, and fetching data from the backend.
    * Chart.js: JavaScript charting tool for visualizing option's prices.

## Features

* **Parameter Input:** Allows users to input standard option pricing parameters:
    * Initial Stock Price ($S_0$)
    * Strike Price ($K$)
    * Risk-Free Rate ($r$)
    * Volatility ($\sigma$)
    * Time to Expiry (in years, $T$)
    * Number of Monte Carlo Simulations
* **Option Pricing:** Computes the estimated prices for both European call and put options using the Monte Carlo simulation based on user-provided inputs.
* **Time Evolution Visualization:** Generates and displays a line chart showing how the estimated call and put option prices change as the time to expiration decreases from the initial $T$ down to zero.
* **Responsive Design:** Basic responsiveness to ensure usability across different device sizes (dependent on included CSS).

## How to Run

To build and run this project, you will need:

* A C++ compiler
* CMake
* The Crow C++ framework

Follow these steps:

1.  **Clone the repository:**
    ```bash
    git clone <repository_url>
    cd <project_directory>
    ```
2.  **Build the C++ backend:**
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```
3.  **Run the backend server:**
    ```bash

    ./build/OptionsPrices
    ```
    The server should start, typically listening on port 8000 (as configured in your C++ `main.cpp`).
4.  **Access the application:** Open your web browser and navigate to `http://localhost:8000`.

## Future Enhancements

* Implement pricing for American options.
* Implement support for exotic options (Asian options).
* Add support for other option pricing models (Black-Scholes for comparison).
* Improve the visualization with interactive features or additional Greeks.
* Enhance the UI/UX.

## Acknowledgements

* The Crow C++ framework developers.
* Chart.js library contributors.
