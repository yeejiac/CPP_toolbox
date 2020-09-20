CFLAGS= -lWs2_32 -w
# -lWs2_32 use for socket
# -w ignore warning
SRC=./src/
SERVER=$(SRC)server.h
CLIENT=$(SRC)client.h
FILEPATH=-I. ./lib/ ./src/
BIN=./bin/
LIB=./lib/
CXX=-std=c++11 -Wall
THREAD=-lpthread
DEBUG= -g

CXXFILE=main.cpp
TARGET=-o test.exe
SERVER_TARGET=-o server.exe
CLIENT_TARGET=-o client.exe

LIBS=$(wildcard $(LIB)*.cpp)
OBJS=$(LIBS:.cpp=.o )

# libfile= $(LIB)logwriter.cpp

main: $(CXXFILE)
	g++ $(CXXFILE) $(BIN)static_package.a \
	$(CXX) $(CLIENT_TARGET) $(CFLAGS) -lstdc++

# %.o: $(LIBS)
# 	g++ -c -fPIC $(FILEPATH) $< -o $(BIN)$@

initParser:
	g++ -c $(LIB)initParser.cpp -o $(BIN)initParser.o

dataQueue:
	g++ -c $(LIB)dataQueue.cpp -o $(BIN)dataQueue.o

logwriter:
	g++ -c $(LIB)logwriter.cpp -o $(BIN)logwriter.o

server:
	g++ -c $(SRC)server.cpp -o $(BIN)server.o

client:
	g++ -c $(SRC)client.cpp -o $(BIN)cliet.o


connection: 
	g++ -c $(FILEPATH)connection.cpp -o $(BIN)connection.o


# OFILE_LIST = initParser.o logwriter.o server.o

%.a: 
	ar crsv $(BIN)$@ $(wildcard $(BIN)*.o)

# mainsocket: $(CXXFILE)
# 	g++ $(CXXFILE) $(SERVER) $(CLIENT) \
# 	$(CXX) $(TARGET) $(CFLAGS)