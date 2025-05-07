cmake_minimum_required(VERSION 3.10)
project(OptionsPrices VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Crow REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)


add_executable(${PROJECT_NAME}
    backend/src/main.cpp
    backend/src/monteCarlo.cpp
)


target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/backend/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


target_link_libraries(${PROJECT_NAME} PRIVATE
    Crow::Crow
    OpenSSL::SSL
    OpenSSL::Crypto
    ZLIB::ZLIB
)