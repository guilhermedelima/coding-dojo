INCDIR=include
SRCDIR=src
LIBDIR=lib
BINDIR=bin
OBJDIR=obj
CC=g++

GTEST_INCDIR=/opt/gtest-1.7.0/include
GMOCK_INCDIR=/opt/gmock-1.7.0/include

CFLAGS=-std=c++0x -W -Wall -isystem $(GTEST_INCDIR) -isystem $(GMOCK_INCDIR) -I$(INCDIR)

DLIBS=-pthread
SLIBS=$(LIBDIR)/libgmock.a $(LIBDIR)/libgtest.a

TARGET=anagrama_main
TEST_TARGET=test_main

HEADER=$(foreach file, $(shell ls $(INCDIR)), $(INCDIR)/$(file))
_OBJ=$(foreach file, $(shell ls $(SRCDIR)), $(OBJDIR)/$(file))
OBJ=$(_OBJ:.cpp=.o)


#### TARGETS ####


.PHONY: clean
  

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADER)
	$(CC) $(CFLAGS) -c -o $@ $<


$(TARGET): $(OBJ) $(SLIBS)
	$(CC) $(CFLAGS) $(DLIBS) -o $(BINDIR)/$@ $^


$(TEST_TARGET): $(OBJ) $(SLIBS)
	$(CC) $(CFLAGS) $(DLIBS) -o $(BINDIR)/$@ $^


clean:
	rm -rf *~ *.out $(BINDIR)/* $(OBJDIR)/* $(INCDIR)/*~ $(SRCDIR)/*~
