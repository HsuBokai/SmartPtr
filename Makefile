ODIR=.
LDIR=./lib
IDIR=./include
CXX=g++
CXXFLAGS= -g -Wall -I$(IDIR) -std=c++11

target1 = main
target2 = main_cpp11_stl
target = $(target1) $(target2) 

$(target1):
	$(CXX) $(CXXFLAGS) -c main.cpp
	$(CXX) $(CXXFLAGS) -o $@ main.o

$(target2):
	$(CXX) -D_CPP11_STL_ $(CXXFLAGS) -c main.cpp
	$(CXX) -D_CPP11_STL_ $(CXXFLAGS) -o $@ main.o

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~ $(target)
