# TCP-KNN
A third part of an ongoing project about vector classification.

<!-- TOC -->
- Markdown Navigation
    - [Description](#Description)
    - [Course of the program](#Course-of-the-program)
    - [Dealing with edge cases](#Dealing-with-edge-cases)
    - [Distances](#Distances)
    - [Installing And Executing](#Installing-And-Executing)
    - [Authors](#Authors)
<!-- /TOC -->

## Description

In this part we were asked to implement a TCP clientSocket connection between a client and a server, that will run in an endless loop and will run our verctor classification algorithm which was implemented in the previeus part.

<img width="300" alt="image" src="https://user-images.githubusercontent.com/112869076/210267297-323a511d-25c7-42ab-9493-fa0617a78b81.png">


The classification algorithm is implemented with the KNN algorithm, which is among the most common of machine learning algorithms and is used in a variety of fields.
The algorithm works as follows:
* Calculation of the distance between the input vector and all classified vectors.
* Finding K nearest neighbors.
* Classify the input vector according to the classification of the majority of neighbors. (using the distance metrics we implemented in the previous part of the assignment)

<img width="501" alt="image" src="https://user-images.githubusercontent.com/112869076/206932807-d6fa4737-e8ad-40cb-b828-bff296607365.png">


Because this project is a continious one, our implementation derived from a wide  
prespective that Lacks of dependence on implementation, in order to expand the project in the future and leverage it.

We used encapsulation for the distance classes and additionally made distance abstract.
Thanks to this, our KNN calculation function that received an object of type Distance could use any of the distance functions independently of them.
In addition, since in the future we may want to change the internal implementation of the vector classification or add additional attributes to it, we implemented the relationship between the client and the server in such a way that does not create a dependency between the implementation of the classification algorithm and the communication process between them.

While planning the task and out of an ambition to improve the running time, we noticed that we don't need to sort the entire database, but it is enough for us to find the K members whose distance is the smallest from the newly inserted vector, and therefore we chose to use the Select algorithm which has an average time complexity of O(n).

## Course of the program

The client sends the information received from the user to the server. The information is received as follows: "vector distance k"
* Vector - a new vector to classify.
* Distance - the distance metric we want to use.
* K - the number of neighbors to acount in the calculation.

The server classified the resulting vector with the KNN algorithm and according to the received metric distance and K (neighbors), and then sends the classification back to the client.

The client prints the received answer to the screen on a separate line and receives the next input from the user.

The client is connected to the same port during the entire program run, but when the client sends "-1" the client will close the socket, on the other hand, the server will continue to listen to the next client.

## Dealing with edge cases

* If the user entered an input not in the order discussed above, the server will return an invalid input message and request a new input.
* In cases where a vector entered by the user does not contain numbers or alternatively is not the appropriate size for the vectors in the database, the server will return an invalid input message and request a new input.
* If the customer enters a distance function corresponding to one of the five distance functions, the server will return an invalid input message and request a new input.
* If the k inserted into the arguments is less than or equal to zero, we will exit the program. Or alternatively if k is greater than the number of vectors in the database, we will turn k into the number of vectors to prevent illegal access.
* In cases where the client was unable to connect to the server's port or IP, we will exit directly from the client's program.
* If the server fails to connect to any port, we will exit the program.
* If the client sends -1 as input to the server, the server will close the communication with the client and wait for the next user, at this time the client will close its socket and end the program.

## Distances

* <a href="https://en.wikipedia.org/wiki/Euclidean_distance">Euclidean distance<a name="">

  <img width="137" alt="image" src="https://user-images.githubusercontent.com/112869076/201759198-da035808-d982-4b36-bc8c-a475d4bb8d48.png">

* <a href="https://en.wikipedia.org/wiki/Taxicab_geometry">Manhattan distance<a name="">

  <img width="117" alt="image" src="https://user-images.githubusercontent.com/112869076/201761310-950f98b8-851c-4e92-b8ec-8c58fe2432d7.png">

  
* <a href="https://en.wikipedia.org/wiki/Chebyshev_distance">Chebyshev distance<a name="">

  <img width="130" alt="image" src="https://user-images.githubusercontent.com/112869076/201761602-326e2be1-445d-47cb-85d3-a339f4257951.png">

  
* <a href="https://en.wikipedia.org/wiki/Canberra_distance">Canberra_distance<a name="">

  <img width="107" alt="image" src="https://user-images.githubusercontent.com/112869076/201761855-d768aa00-8525-452d-b4d0-b5a285eb2866.png">

  
* <a href="https://en.wikipedia.org/wiki/Minkowski_distance">Minkowski distance<a name="">

  <img width="173" alt="image" src="https://user-images.githubusercontent.com/112869076/201762252-08b6bad3-ce25-442d-b172-f130fd42c5e5.png">


## Installing And Executing
    
To clone and run this application, you'll need [Git](https://git-scm.com) installed on your computer.
  
From your command line:

  
```bash
# Clone this repository.
$ git clone https://github.com/tomerp1812/TCP-KNN

# Go into the repository.
$ cd TCP-KNN

# Compile using makefile.
$ make
```

```bash
# Run the program on Linux:
$ ./server.out "path to a classified file" port
$ ./client.out ip port
```

```bash
# Run the program on Windows:
$ server.out "path to a classified file" port
$ client.out ip port
```

  
## Authors
- [Dan Saada](https://github.com/DanSaada)
- [Tomer Peisikov](https://github.com/tomerp1812)
