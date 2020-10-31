link: QueType PriorityQueue Customer BankSimulation.cpp
	g++ -Wall -g -pedantic-errors -o p3 QueType.o PriorityQueue.o Customer.o BankSimulation.cpp

Customer: Customer.cpp Customer.h
	g++ -c -Wall -g -pedantic-errors Customer.cpp

QueType: ./req/QueType.cpp ./req/QueType.h
	g++ -c -Wall -g -pedantic-errors ./req/QueType.cpp

PriorityQueue: ./req/PriorityQueue.cpp ./req/PriorityQueue.h
	g++ -c -Wall -g -pedantic-errors ./req/PriorityQueue.cpp

run:
	./p3

clean:
	/bin/rm *.o p3