cmake_minimum_required(VERSION 3.6)
project(ex33)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp BFS.cpp BFS.h Cab.cpp Cab.h Driver.cpp Driver.h Element.cpp Element.h Grid.cpp Grid.h Luxury.cpp Luxury.h MainFlow.cpp MainFlow.h Map.cpp Map.h Matrix.cpp Matrix.h Passenger.cpp Passenger.h Point.cpp Point.h Regular.cpp Regular.h Square.cpp Square.h TaxiCenter.cpp TaxiCenter.h Trip.cpp Trip.h Value.cpp Value.h Client.cpp Client.h Server.cpp Server.h)
add_executable(ex33 ${SOURCE_FILES})