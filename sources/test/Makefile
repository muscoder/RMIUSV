all: test_name
test_name: test.o
	gcc test.o -lbcm2835 -o test
test.o: test.c
	gcc -c test.c
clean: 
	rm -rf *o test_name 