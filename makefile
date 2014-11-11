

CC = gcc
CFLAGS = -O3
LIBS = -lm -lgsl -lgslcblas


HEADERS = E2_func.h
OBJECTS = E2_func.o E2_main.o 
PROGRAM = E2

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f *.o
	touch *.c


