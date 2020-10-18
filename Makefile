CFLAGS= -lWs2_32 -w 
# -lWs2_32 use for socket
# -w ignore warning
SOCKET=./socket/
SERVER=$(SOCKET)server.cpp
CLIENT=$(SOCKET)client.cpp
FILEPATH=-I. ./lib/ ./src/
LIB=-lcommon -lstdc++ -lpthread
LIBPATH=./lib/
CXX=-std=c++11 -Wall
THREAD=-lpthread
DEBUG=-DDEBUG -g

CXXFILE=main.cpp
TARGET=-o test.exe
SERVER_TARGET=-o server.exe
CLIENT_TARGET=-o client.exe

LIBS=$(wildcard $(LIB)*.cpp)
OBJS=$(LIBS:.cpp=.o )


main: $(CXXFILE)
	g++ $(DEBUG) $(CXXFILE) ./socket/connection.cpp $(SERVER) $(LIB) \
	$(CXX) $(SERVER_TARGET) $(CFLAGS)

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
	g++ -c $(SOCKET)client.cpp -o $(LIBPATH)client.o

connection: 
	g++ -c $(FILEPATH)connection.cpp -o $(BIN)connection.o

%.a: 
	ar crsv $(LIBPATH)$@ $(wildcard $(LIBPATH)*.o)

# mainsocket: $(CXXFILE)
# 	g++ $(CXXFILE) $(SERVER) $(CLIENT) \
# 	$(CXX) $(TARGET) $(CFLAGS)