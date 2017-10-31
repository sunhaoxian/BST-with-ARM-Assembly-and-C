CC=gcc
AS=as
ASSIGNMENT_PATH=~/../public/pa4/

count.o: count.s
	as -o $@ $<
totalLength.o: totalLength.s
	as -o $@ $<
clean:
	rm -f main *.o core* *~

test: test.run
	./test.run

vtest: test.run
	valgrind --leak-check=full --under-value-errors=no ./test.run

test.run: bst.o test.c runtests.c
	gcc -Wall -g -o test.run test.c runtests.c cutest/CuTest.c bst.o count.o totalLength.o

bst.o: bst.h bst.c
	gcc -Wall -g -c -o bst.o bst.c

testbst%.run: $(ASSIGNMENT_PATH)/bst%.o test.c runtests.c
	gcc -Wall -o $@ test.c runtests.c cutest/CuTest.c $<
