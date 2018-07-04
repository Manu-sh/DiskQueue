CFLAGS=-O3 -ffast-math -Wall -Wextra -pedantic -std=c11 -pipe
.PHONY: all clean

INCLUDE=../include
MY_STATIC_LIB=libdiskqueue.a

$(MY_STATIC_LIB): $(MY_STATIC_LIB)(DiskArray.o) $(MY_STATIC_LIB)(DiskQueue.o)

%.o: %.c
	$(CC) -c $(CFLAGS) -I $(INCLUDE) $<

clean:
	rm -rf *.o *.a
