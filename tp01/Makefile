CC = gcc
CFLAGS = -Wall
TARGET = iplot

all: $(TARGET)

$(TARGET): main.o iplot.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o iplot.o

main.o: main.c iplot.h
	$(CC) $(CFLAGS) -c main.c

iplot.o: iplot.c iplot.h
	$(CC) $(CFLAGS) -c iplot.c

clean:
	rm -f *.o $(TARGET)
