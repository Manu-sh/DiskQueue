INCLUDE=../include
MY_STATIC_LIB=libdiskqueue.a

LDLIBS=-lgdbm -lgdbm_compat
CXXFLAGS=-Wall -Wextra -pedantic -std=c++11 -fstack-protector-strong

.PHONY: all clean

test:
	@./test.sh

test_diskqueue: test_diskqueue.cpp 
	make clean
	./gen_nsrc.rb 100
	CFLAGS='-fstack-protector-strong' make -C ../src
	$(CXX) $(CXXFLAGS) -o $@ $< ../src/$(MY_STATIC_LIB) $(LDLIBS) -I $(INCLUDE)

test_diskarray: test_diskarray.cpp 
	make clean
	./gen_nsrc.rb 100
	CFLAGS='-fstack-protector-strong' make -C ../src
	$(CXX) $(CXXFLAGS) -o $@ $< ../src/$(MY_STATIC_LIB) $(LDLIBS) -I $(INCLUDE)

clean:
	make clean -C ../src
	rm -rf test_diskarray unit_test_diskarray.* nums.dat
	rm -rf test_diskqueue unit_test_diskqueue.*
