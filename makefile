# MAKEFILE

CC = g++
PROG_NAME = Tests
SOURCE = main-test.cpp TexteEnBoite.cpp


all : $(PROG_NAME)


main-test.o : main-test.cpp
	$(CC) -std=c++11 -c main-test.cpp

TexteEnBoite.o : TexteEnBoite.cpp
	$(CC) -std=c++11 -c TexteEnBoite.cpp

$(PROG_NAME) : $(SOURCE:.cpp=.o)
	$(CC) $(SOURCE:.cpp=.o) -o $(PROG_NAME)
