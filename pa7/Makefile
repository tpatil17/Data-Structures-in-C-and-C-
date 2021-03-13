#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 7
#
#  make                     makes Arithmetic
#  make ListTest            makes ListTest
#  make BigIntegerTest      makes BigIntegerTest
#  make clean               removes all binaries
#  make memcheck            tests for memory leaks
#------------------------------------------------------------------------------

CLIENT         = Arithmetic
ADT1           = BigInteger
ADT2           = List
LIST_TEST      = ListTest
BI_TEST	       = BigIntegerTest
SOURCE         = $(CLIENT).c
OBJECT         = $(CLIENT).o
LIST_TEST_SOURCE = $(LIST_TEST).c
LIST_TEST_OBJECT = $(LIST_TEST).o
BI_TEST_SOURCE = $(BI_TEST).c
BI_TEST_OBJECT = $(BI_TEST).o
ADT1_SOURCE    = $(ADT1).c
ADT1_OBJECT    = $(ADT1).o
ADT1_HEADER    = $(ADT1).h
ADT2_SOURCE    = $(ADT2).c
ADT2_OBJECT    = $(ADT2).o
ADT2_HEADER    = $(ADT2).h
COMPILE        = gcc -lm -c -std=c11 -Wall
LINK           = gcc -lm -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full



$(CLIENT) : $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(CLIENT) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

$(LIST_TEST) : $(LIST_TEST_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(LIST_TEST) $(LIST_TEST_OBJECT) $(ADT2_OBJECT)

$(BI_TEST) : $(BI_TEST_OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(BI_TEST) $(BI_TEST_OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

$(OBJECT) : $(SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(SOURCE)

$(LIST_TEST_OBJECT) : $(LIST_TEST_SOURCE) $(ADT2_HEADER)
	$(COMPILE) $(LIST_TEST_SOURCE)

$(BI_TEST_OBJECT) : $(BI_TEST_SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(BI_TEST_SOURCE)

$(ADT1_OBJECT) : $(ADT1_SOURCE) $(ADT1_HEADER)
	$(COMPILE) $(ADT1_SOURCE)

$(ADT2_OBJECT) : $(ADT2_SOURCE) $(ADT2_HEADER)
	$(COMPILE) $(ADT2_SOURCE)

clean :
	$(REMOVE) $(CLIENT) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT) $(LIST_TEST) $(LIST_TEST_OBJECT) $(BI_TEST) $(BI_TEST_OBJECT)

memcheck : $(CLIENT)
	$(MEMCHECK) $(CLIENT) in3 myout3
