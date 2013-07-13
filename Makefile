CC=g++
CFLAGS=`pkg-config opencv --cflags`
LIBS=`pkg-config opencv --libs`

all: omar test vartest source.pdf

omar: omar.o align.o tournament.o page.o question.o
	$(CC) omar.o align.o tournament.o page.o question.o -o omar $(CFLAGS) $(LIBS)

test: test.o align.o tournament.o page.o question.o
	$(CC) test.o align.o tournament.o page.o question.o -o test $(CFLAGS) $(LIBS)

vartest: variables.cpp
	$(CC) variables.cpp -o vartest -g $(CFLAGS) $(LIBS)

source.pdf: source.tex
	pdflatex ./source.tex
	pdflatex ./source.tex

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

clean:
	rm -rf *.o test omar source.pdf source.aux source.pos source.cal source.log

