server: Server.o classificationLogic.o Distance.o Canberra.o Catalog.o Chebyshev.o Database.o Euclidean.o Manhattan.o Minkowski.o
	g++ -std=c++11 -Wall -o server.out Server.o classificationLogic.o Distance.o Canberra.o Catalog.o Chebyshev.o Database.o Euclidean.o Manhattan.o Minkowski.o

client: client.o
	g++ -std=c++11 -Wall -o client.out client.o

client.o: client.cpp
	g++ -std=c++11 -Wall -c client.cpp

Server.o: Server.cpp
	g++ -std=c++11 -Wall -c Server.cpp

classificationLogic.o: classificationLogic.cpp
	g++ -std=c++11 -Wall -c classificationLogic.cpp

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
	rm -f *.o server.out client.out

