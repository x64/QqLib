cmake_minimum_required(VERSION 3.16)

project(QqThread LANGUAGES CXX)

enable_testing()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(QqThread tst_QqThread.cpp
    WorkerThread02.h)
add_test(NAME QqThread COMMAND QqThread)

target_link_libraries(QqThread PRIVATE Qt${QT_VERSION_MAJOR}::Test)

