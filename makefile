CC = gcc
CFLAGS = -Wall -O2 -lm
TARGET = l1

all: $(TARGET)

$(TARGET): l1.c
	$(CC) -o $(TARGET) l1.c $(CFLAGS)

clean:
	rm -f $(TARGET) *.o

