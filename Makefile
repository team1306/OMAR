CC=g++
CFLAGS=`pkg-config opencv --cflags`
LIBS=`pkg-config opencv --libs`

all:
	$(MAKE) -C ./src all
	$(MAKE) -C ./tex all

clean:
	$(MAKE) -C ./src clean
	$(MAKE) -C ./tex clean
	$(MAKE) -C ./build clean

