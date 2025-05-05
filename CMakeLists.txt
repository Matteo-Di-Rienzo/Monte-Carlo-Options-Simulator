cmake_minimum_required(VERSION 3.10)
project(OptionsPrices VERSION 0.1) # Renamed project for clarity

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Crow (assuming Crow is installed or findable by CMake)
find_package(Crow REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

# Define the main executable
add_executable(${PROJECT_NAME}
    backend/src/main.cpp
    backend/src/monteCarlo.cpp
)

# Add include directories
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/backend/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Crow::Crow
    OpenSSL::SSL
    OpenSSL::Crypto
    ZLIB::ZLIB
)