cmake_minimum_required(VERSION 3.6)
project(ex4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")


set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.58.0 COMPONENTS serialization system log)
include_directories(${Boost_INCLUDE_DIR})
add_definitions(-DBOOST_ALL_DYN_LINK)

set(SOURCE_FILES_CLIENT BFS.cpp BFS.h Cab.cpp Cab.h Driver.cpp Driver.h Element.cpp
        Element.h Grid.cpp Grid.h Luxury.cpp Luxury.h MainFlow.cpp MainFlow.h Map.cpp Map.h
        Matrix.cpp Matrix.h Passenger.cpp Passenger.h Point.cpp Point.h Regular.cpp Regular.h
        Square.cpp Square.h TaxiCenter.cpp TaxiCenter.h Trip.cpp Trip.h Value.cpp Value.h
        Client.cpp Client.h Clock.cpp Clock.h Socket.cpp Socket.h Tcp.cpp Tcp.h Udp.cpp Udp.h)

set(SOURCE_FILES_SERVER BFS.cpp BFS.h Cab.cpp Cab.h Driver.cpp Driver.h Element.cpp
        Element.h Grid.cpp Grid.h Luxury.cpp Luxury.h MainFlow.cpp MainFlow.h Map.cpp Map.h
        Matrix.cpp Matrix.h Passenger.cpp Passenger.h Point.cpp Point.h Regular.cpp Regular.h
        Square.cpp Square.h TaxiCenter.cpp TaxiCenter.h Trip.cpp Trip.h Value.cpp Value.h
        Server.cpp Server.h Clock.cpp Clock.h Socket.cpp Socket.h Tcp.cpp Tcp.h Udp.cpp Udp.h)

add_executable(Server ${SOURCE_FILES_SERVER})
add_executable(Client ${SOURCE_FILES_CLIENT})

target_link_libraries(Server ${Boost_LIBRARIES})
target_link_libraries(Client ${Boost_LIBRARIES})