CC=g++
CFLAGS=-std=c++11

all: Column.o Database.o Statement.o Transaction.o

Column.o: Column.cpp
	$(CC) -c Column.cpp $(CFLAGS)

Database.o: Database.cpp
	$(CC) -c Database.cpp $(CFLAGS)

Statement.o: Statement.cpp
	$(CC) -c Statement.cpp $(CFLAGS)

Transaction.o: Transaction.cpp
	$(CC) -c Transaction.cpp $(CFLAGS)

clean:
	rm -rf ./*.o