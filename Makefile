GCC ?= g++

HEADERS := image.h haar.h stdio-wrapper.h

all: build

build: vj

image.o: image.c $(HEADERS)
	$(GCC) -g -o $@ -c $<

stdio.o: stdio-wrapper.c $(HEADERS)
	$(GCC) -g -o $@ -c $<

main.o: main.cpp $(HEADERS)
	$(GCC) -g -o $@ -c $<

haar.o: haar.cpp $(HEADERS)
	$(GCC) -g -lpthread -o $@ -c $<

rectangles.o: rectangles.cpp $(HEADERS)
	$(GCC) -g -o $@ -c $<

vj: main.o haar.o image.o stdio-wrapper.o rectangles.o
	$(GCC) -g -lpthread -o $@ $+ $(LDFLAGS)

run: build
	./vj

clean:
	rm -f vj *.o Output.pgm
