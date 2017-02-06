CXXFLAGS= -I. 
CXXFLAGS+=-g
CXXFLAGS+=-O2 
CXXFLAGS+=-std=c++11
CXXFLAGS+=-Werror -Wno-sign-conversion -Wconversion -Wall \
		  -Wno-unused-parameter -Woverloaded-virtual -Wextra \
		  -Wpointer-arith -Wshadow

TESTS=sample
OBJS=conhash.o 
LIB=libconhash.a

all: $(TESTS) $(LIB)

$(TESTS):
	g++ $(CXXFLAGS) -o $@ $(filter %.cc, $^)

$(LIB) : $(OBJS)
	rm -f $@
	ar cr $@ $(OBJS)
	rm -f $(OBJS)

tags :
	ctags -R *

sample: sample.cc conhash.cc 

.PHONY: clean
clean:
	rm -f $(TESTS) $(OBJS) $(LIB)
