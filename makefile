a.out: main.o Distance.o Canberra.o Catalog.o Chebyshev.o Database.o Euclidean.o Manhattan.o Minkowski.o
	g++ -std=c++11 -Wall -o a.out main.o Distance.o Canberra.o Catalog.o Chebyshev.o Database.o Euclidean.o Manhattan.o Minkowski.o

main.o: Server.cpp
	g++ -std=c++11 -Wall -c main.cpp

Distance.o: Distance.cpp
	g++ -std=c++11 -Wall -c Distance.cpp

Canberra.o: Canberra.cpp
	g++ -std=c++11 -Wall -c Canberra.cpp
 
 Catalog.o: Catalog.cpp
	g++ -std=c++11 -Wall -c Catalog.cpp
 
 Chebyshev.o: Chebyshev.cpp
	g++ -std=c++11 -Wall -c Chebyshev.cpp
 
 Database.o: Database.cpp
	g++ -std=c++11 -Wall -c Database.cpp
 
 Euclidean.o: Euclidean.cpp
	g++ -std=c++11 -Wall -c Euclidean.cpp
 
 Manhattan.o: Manhattan.cpp
	g++ -std=c++11 -Wall -c Manhattan.cpp
 
 Minkowski.o: Minkowski.cpp
	g++ -std=c++11 -Wall -c Minkowski.cpp

clean:
	rm -f *.o a.out




