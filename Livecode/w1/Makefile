CXXFLAGS=-std=c++20 -Wall -Wextra -Werror -O3 -march=native

BASENAMES=p1 p2 p3 p4
TARGETS=$(BASENAMES:=.exe)

all: $(TARGETS)

clean:
	rm -f *.exe

%.exe: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<