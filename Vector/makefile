target: driver.o tvector.o
	g++ -std=c++11 driver.o -o tvector

driver.o: driver.cpp
	g++ -std=c++11 -c driver.cpp

tvector.o: tvector.h
	g++ -std=c++11 -c tvector.h
clean:
	rm *.o
