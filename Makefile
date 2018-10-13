build: main

main: main.cpp robot.h queue.h stack.h functions.h structures.h
	g++ -Wall -std=c++11 main.cpp -o main

clean:
	rm -f main *.o
