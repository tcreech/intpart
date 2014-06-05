CPPFLAGS = -I.

all:	intpart_test

test:	intpart_test
	./intpart_test

debugtest: intpart_test
	cgdb -- --args ./intpart_test

intpart_test:	intpart.o intpart_test.o
	$(CC) intpart.o intpart_test.o -o intpart_test

intpart.o:	intpart.c intpart.h

clean:
	-rm -f intpart_test intpart.o intpart_test.o

