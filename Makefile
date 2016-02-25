ODIR=.
LDIR=./lib
IDIR=./include
CXX=g++
CXXFLAGS= -g -Wall -I$(IDIR) -std=c++11

_DEPS = smartPtr.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

target = main

$(target): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(ODIR)/%.o: %.c $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~ $(target)
