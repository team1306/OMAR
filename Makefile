CC=g++
CFLAGS=`pkg-config opencv --cflags` -g
LIBS=`pkg-config opencv --libs`

all: test page.o question.o project.o

test: test.o align.o project.o page.o question.o
	$(CC) test.o align.o project.o page.o question.o -o test $(CFLAGS) $(LIBS)

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