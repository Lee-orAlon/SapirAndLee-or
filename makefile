
all: server client

# Put here all the common files which are being used both in client and server
COMMON_SOURCES = Cab.cpp Driver.cpp Element.cpp Luxury.cpp Passenger.cpp Point.cpp Regular.cpp Socket.cpp Square.cpp Trip.cpp Udp.cpp Value.cpp

server:
	g++ -std=c++0x Server.cpp MainFlow.cpp BFS.cpp Clock.cpp Grid.cpp Map.cpp Matrix.cpp TaxiCenter.cpp $(COMMON_SOURCES) -lboost_serialization -D _DISABLE_LOGS -I. -o server.out

client:
	g++ -std=c++0x Client.cpp $(COMMON_SOURCES) -lboost_serialization -D _DISABLE_LOGS -I. -o client.out

