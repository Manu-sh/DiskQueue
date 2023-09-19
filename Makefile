LDLIBS=-lgdbm -lgdbm_compat
CXXFLAGS=-O3 -ffast-math -Wall -Wextra -pedantic -std=c++11 -pipe #-march=native -mtune=native
.PHONY: all clean

all: main.cpp src/libdiskqueue.a OpenQueue.o
	$(CXX) $(CXXFLAGS) -o main main.cpp OpenQueue.o src/libdiskqueue.a $(LDLIBS) -I include

#all: main.cpp src/libdiskqueue.a
#	$(CXX) $(CXXFLAGS) -o main main.cpp src/libdiskqueue.a $(LDLIBS) -I include

OpenQueue.o: OpenQueue.cpp OpenQueue.hpp
	$(CXX) $(CXXFLAGS) -c OpenQueue.cpp -I include

src/libdiskqueue.a:
	make -C src

clean:
	rm -rf main *.o
	make clean -C src
