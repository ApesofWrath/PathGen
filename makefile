CC      = g++
CFLAGS  = -I./include/
LDFLAGS = -lpathfinder

all: trajgen clean

trajgen: trajgen.o
	$(CC) -o $@ $^ $(LDFLAGS)

trajgen.o: trajgen.cpp
	$(CC) -c $(CFLAGS) $<

.PHONY: clean cleanest

clean:
	rm *.o

cleanest: clean
	rm trajgen
