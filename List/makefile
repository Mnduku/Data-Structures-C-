target: test_list.o
	g++ -std=c++11 test_list.o -o list

test_list.o: test_list.cpp
	g++ -std=c++11 -c test_list.cpp

List.o: List.h
	g++ -std=c++11 -c List.h

clean:
	rm *o
