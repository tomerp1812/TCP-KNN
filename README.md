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

In this part we were asked to implement a TCP socket connection between a client and a server, that will run in an endless loop our verctor classification algorithm which was implemented in the previeus part with the KNN algorithm, which is among the most common of machine learning algorithms and is used in a variety of fields.

The algorithm works as follows:
* Calculation of the distance between the input vector and all classified vectors.
* Finding K nearest neighbors.
* Classify the input vector according to the classification of the majority of neighbors. (using the distance metrics we implemented in the previous part of the assignment)

<img width="501" alt="image" src="https://user-images.githubusercontent.com/112869076/206932807-d6fa4737-e8ad-40cb-b828-bff296607365.png">


Because this project is a continious one, our implementation derived from a wide 
prespective that Lacks of dependence on implementation, in order to expand the project in the future and leverage it.

We used encapsulation for the distance classes and additionally made distance abstract.
Thanks to this, our KNN calculation function that received an object of type Distance could use any of the distance functions independently of them.

While planning the task and out of an ambition to improve the running time, we noticed that we don't need to sort the entire database, but it is enough for us to find the K members whose distance is the smallest from the newly inserted vector, and therefore we chose to use the Select algorithm which has an average time complexity of O(n).

## Course of the program

First in the command line, the program gets inputs for size K, file, and distance in the following format: "a.out k file distance"
* K - the number of neighbors to acount in the calculation.
* File- the name of the classified vector file.
* Distance - the distance metric we want to use.

Then, when an input is entered to the screen (a vector) the program will print the classification of that vector, using the KNN algorithm, accordingly
to the entered k, file and distance and wait for the next input indefinitely.

## Dealing with edge cases

* If a user entered incorrect path or a string that does not match any of the 5 distance functions, we exit the program.
* In cases where a vector entered by the user doesn't contain numbers or alternatively isn't in the appropriate size for the vectors in the database, the program       will print an error and request a new input.
* For vectors that are already classified, we will look at the length of the first vector entered into the database and based on that we will decide whether to       enter vectors into the database or not. That is, we will not insert them when their length does not match his.
* If the k inserted in the arguments is less than or equal to zero, we will exit the program. Or alternatively if k is greater than the number of vectors in the       database we will make k the same as the number of vectors to prevent illegal access.

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
$ ./a.out K "path to a classified file" Distance algorithm
```

```bash
# Run the program on Windows:
$ a.out K "path to a classified file" Distance algorithm
```

  
## Authors
- [Dan Saada](https://github.com/DanSaada)
- [Tomer Peisikov](https://github.com/tomerp1812)
