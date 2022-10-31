CC=g++
CFLAGS=-std=c++11 -pthread -lpcap
OBJS=backend.o utils/request.o utils/sender.o utils/beacon.o
TARGET=backend

all: $(TARGET)

clean:
	rm -f *.o
	rm -f utils/*.o	

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

backend.o: backend.c utils/sender.h utils/request.h
utils/request.o: utils/request.cpp utils/request.h
utils/sender.o: utils/sender.c utils/sender.h utils/beacon.h utils/request.h
utils/beacon.o: utils/beacon.c utils/beacon.h


