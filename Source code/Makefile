#CFLAGS=-g -Wall -std=c++11
CFLAGS= -Wall -std=c++11
OPT= -O

all: grouping_ils
grouping_ils: grouping_ils.o
	c++ $(OPT) $(CFLAGS) -o grouping_ils grouping_ils.o
.cpp.o:
	c++ $(CFLAGS) -c $<
clean:
	/bin/rm -f grouping_ils *.o *~
