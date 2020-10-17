CFLAGS= -lWs2_32 -w -shared 
LIBPATH=../lib/
FILEPATH=-I. ./funclib/ ./src/

CXX=-std=c++11 -Wall
THREAD=-lpthread
DEBUG= -g

function=initParser.o dataQueue.o logwriter.o

initParser:
	g++ -c -DBDLL $(LIB)initParser.cpp -o $(LIBPATH)initParser.o

dataQueue:
	g++ -c -DBDLL $(LIB)dataQueue.cpp -o $(LIBPATH)dataQueue.o

logwriter:
	g++ -c -DBDLL $(LIB)logwriter.cpp -o $(LIBPATH)logwriter.o

%.a: 
	ar crsv $(LIBPATH)$@ $(wildcard $(LIBPATH)*.o)

# %.lib:
# 	g++ -shared -o $(LIBPATH)$@ $(wildcard $(LIBPATH)*.o)


