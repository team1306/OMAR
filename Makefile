CC=g++
CFLAGS=`pkg-config opencv --cflags`
LIBS=`pkg-config opencv --libs`

all: omar test

omar: omar.o align.o project.o page.o question.o
	$(CC) omar.o align.o project.o page.o question.o -o omar $(CFLAGS) $(LIBS)

test: test.o align.o project.o page.o question.o
	$(CC) test.o align.o project.o page.o question.o -o test $(CFLAGS) $(LIBS)

omar.o: omar.cpp
	$(CC) -c omar.cpp $(CFLAGS)

main.o: main.cpp
	$(CC) -c main.cpp $(CFLAGS)

test.o: test.cpp
	$(CC) -c test.cpp $(CFLAGS)

project.o: project.cpp
	$(CC) -c project.cpp $(CFLAGS)

align.o: align.cpp
	$(CC) -c align.cpp $(CFLAGS)

question.o: question.cpp
	$(CC) -c question.cpp $(CFLAGS)

page.o: page.cpp
	$(CC) -c page.cpp $(CFLAGS)

clean:
	rm -rf *.o test