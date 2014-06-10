CPPFLAGS = -I.
CFLAGS = -O0 -g

all:	intpart_test stresstest

test:	intpart_test
	./intpart_test

debugtest: intpart_test
	cgdb -- --args ./intpart_test

intpart_test:	intpart.o intpart_test.o
	$(CC) intpart.o intpart_test.o -o intpart_test

stresstest:	intpart.o stresstest.c
	$(CC) $(CFLAGS) -fopenmp intpart.o stresstest.c -o $@

intpart.o:	intpart.c intpart.h

clean:
	-rm -f intpart_test intpart.o intpart_test.o stresstest

