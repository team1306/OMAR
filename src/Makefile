CC=g++
CFLAGS=`pkg-config opencv --cflags` -I./../include -std=c++11 -g
LIBS=`pkg-config opencv --libs` -l sqlite3

all: SQLiteCpp omar vartest

omar: omar.o tournament.o page.o question.o database.o report.o checkbox.o number.o multiplechoice.o field.o SQLiteCpp
	$(CC) omar.o tournament.o page.o question.o database.o report.o checkbox.o number.o multiplechoice.o field.o ./SQLiteCpp/Column.o ./SQLiteCpp/Database.o ./SQLiteCpp/Statement.o ./SQLiteCpp/Transaction.o -o ../build/omar -g $(CFLAGS) $(LIBS)

test: test.o tournament.o page.o question.o database.o report.o checkbox.o number.o multiplechoice.o field.o SQLiteCpp
	$(CC) test.o tournament.o page.o question.o database.o report.o checkbox.o number.o multiplechoice.o field.o ./SQLiteCpp/Column.o ./SQLiteCpp/Database.o ./SQLiteCpp/Statement.o ./SQLiteCpp/Transaction.o -o ../build/test $(SQLITE_CFLAGS) $(CFLAGS) $(LIBS)

vartest: variables.cpp
	$(CC) variables.cpp -o ../build/vartest -g $(CFLAGS) $(LIBS)

validate: validation.o 
	$(CC) validation.o  -o ../build/validate -g $(CFLAGS) $(LIBS)

SQLiteCpp:
	$(MAKE) -C ./SQLiteCpp all

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

question.o: question.cpp
	$(CC) -c question.cpp $(CFLAGS)

page.o: page.cpp
	$(CC) -c page.cpp $(CFLAGS)

database.o: database.cpp
	$(CC) -c database.cpp $(SQLITE_CFLAGS) $(CFLAGS)

report.o: report.cpp
	$(CC) -c report.cpp $(SQLITE_CFLAGS) $(CFLAGS)

checkbox.o: checkbox.cpp
	$(CC) -c checkbox.cpp $(CFLAGS)

number.o: number.cpp
	$(CC) -c number.cpp $(CFLAGS)

multiplechoice.o: multiplechoice.cpp
	$(CC) -c multiplechoice.cpp $(CFLAGS)

field.o: field.cpp
	$(CC) -c field.cpp $(CFLAGS)

clean:
	rm -rf *.o
	$(MAKE) -C ./SQLiteCpp clean