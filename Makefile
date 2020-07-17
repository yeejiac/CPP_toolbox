SRC=./src/
SERVER=$(SRC)server.h
CLIENT=$(SRC)client.h

BIN=./bin/
CXX=-std=c++11 -Wall 
THREAD=-lpthread
DEBUG=-DDEBUG -g

CXXFILE=main.cpp
TARGET=-o $(BIN)test.out

mainsocket: $(CXXFILE)
	g++ $(CXXFILE) $(SERVER) $(CLIENT) \
	$(CXX) $(TARGET)