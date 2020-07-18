CFLAGS=-I.

SRC=./src/
SERVER=$(SRC)server.h
CLIENT=$(SRC)client.h

BIN=./bin/
LIB=./lib/
CXX=-std=c++11 -Wall 
THREAD=-lpthread
DEBUG=-DDEBUG -g

CXXFILE=main.cpp
TARGET=-o test.out

SRCS=$(wildcard $(LIB)*.cpp)
OBJS=$(SRCS:.cpp=.o )

libfile= $(LIB)logwriter.cpp

%.o: $(SRCS)
	g++ -c $< -o $(BIN)$@

%.a: 
	ar crsv $@ $(wildcard $(BIN)*.o)

main: $(CXXFILE)
	g++ $(CXXFILE) lib.a \
	$(CXX) $(TARGET) $(CFLAGS)

mainsocket: $(CXXFILE)
	g++ $(CXXFILE) $(SERVER) $(CLIENT) \
	$(CXX) $(TARGET) $(CFLAGS)