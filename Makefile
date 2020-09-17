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
DEBUG=-DDEBUG -g

CXXFILE=main.cpp
TARGET=-o test.exe

LIBS=$(wildcard $(LIB)*.cpp)
OBJS=$(LIBS:.cpp=.o )

# libfile= $(LIB)logwriter.cpp

main: $(CXXFILE)
	g++ $(CXXFILE) $(BIN)static_package.a \
	$(CXX) $(TARGET) $(CFLAGS)

# %.o: $(LIBS)
# 	g++ -c -fPIC $(FILEPATH) $< -o $(BIN)$@

initParser:
	g++ -c $(LIB)initParser.cpp -o $(BIN)initParser.o

logwriter:
	g++ -c $(LIB)logwriter.cpp -o $(BIN)logwriter.o

server:
	g++ -c $(SRC)server.cpp -o $(BIN)server.o

connection: 
	g++ -c $(FILEPATH)connection.cpp -o $(BIN)connection.o


# OFILE_LIST = initParser.o logwriter.o server.o

%.a: 
	ar crsv $(BIN)$@ $(wildcard $(BIN)*.o)

# mainsocket: $(CXXFILE)
# 	g++ $(CXXFILE) $(SERVER) $(CLIENT) \
# 	$(CXX) $(TARGET) $(CFLAGS)