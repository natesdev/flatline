CC = g++
CFLAGS = -c -fPIC
TARGET_LIB = libflatline.a
INCLUDE_DIR = /usr/include
LIB_DIR = /usr/lib

all: $(TARGET_LIB)

flatline.o: flatline.cpp
	$(CC) $(CFLAGS) flatline.cpp -o flatline.o

$(TARGET_LIB): flatline.o
	ar rcs $(TARGET_LIB) flatline.o

install:
	cp flatline.h $(INCLUDE_DIR)/
	cp $(TARGET_LIB) $(LIB_DIR)/

clean:
	rm -f *.o $(TARGET_LIB)
