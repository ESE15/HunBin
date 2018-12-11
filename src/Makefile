CC=gcc
INCLUDE=-I../include
LIB=-L../lib
LIBNAME=-lhunbin
OBJS=main.o
OUTPUT=HBmake
CFLAGS=-Wall


all : $(OUTPUT)


$(OUTPUT): $(OBJS)
	$(CC) -o $(OUTPUT) $(OBJS) $(LIB) $(LIBNAME)

%.o: %.c ../include/JH_SEARCH.h ../include/YB_SCRIPT.h
	$(CC) -c $(CFLAGS) $< $(INCLUDE) -o $@

clean:
	rm -f $(OUTPUT) $(OBJS)
