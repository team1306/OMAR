CC=g++
CFLAGS=`pkg-config opencv --cflags`
LIBS=`pkg-config opencv --libs` -l sqlite3

SQLITE_CFLAGS=-I./../include -std=c++11

all: omar vartest

omar: omar.o align.o tournament.o page.o question.o
	$(CC) omar.o align.o tournament.o page.o question.o -o ../build/omar -g $(CFLAGS) $(LIBS)

test: test.o align.o tournament.o page.o question.o
	$(CC) test.o align.o tournament.o page.o question.o -o ../build/test $(CFLAGS) $(LIBS)

vartest: variables.cpp
	$(CC) variables.cpp -o ../build/vartest -g $(CFLAGS) $(LIBS)

validate: validation.o align.o
	$(CC) validation.o align.o -o ../build/validate -g $(CFLAGS) $(LIBS)

validation.o: validation.cpp
	$(CC) -c validation.cpp $(CFLAGS)

omar.o: omar.cpp
	$(CC) -c omar.cpp $(CFLAGS)

main.o: main.cpp
	$(CC) -c main.cpp $(CFLAGS)

test.o: test.cpp
	$(CC) -c test.cpp $(CFLAGS)

tournament.o: tournament.cpp
	$(CC) -c tournament.cpp $(CFLAGS)

align.o: align.cpp
	$(CC) -c align.cpp $(CFLAGS)

question.o: question.cpp
	$(CC) -c question.cpp $(CFLAGS)

page.o: page.cpp
	$(CC) -c page.cpp $(CFLAGS)

database.o: database.cpp
	$(CC) -c database.cpp $(SQLITE_CFLAGS) $(CFLAGS)

clean:
	rm -rf *.o