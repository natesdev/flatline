CC = g++
CFLAGS = -c -fPIC
TARGET_LIB = libflatline.a
INCLUDE_DIR = /usr/include
LIB_DIR = /usr/lib

all: $(TARGET_LIB)

csv.o: csv.cpp
	$(CC) $(CFLAGS) csv.cpp -o csv.o

$(TARGET_LIB): csv.o
	ar rcs $(TARGET_LIB) csv.o

install:
	cp csv.h $(INCLUDE_DIR)/flatline.h
	cp $(TARGET_LIB) $(LIB_DIR)/

clean:
	rm -f *.o $(TARGET_LIB)
