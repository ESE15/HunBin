CC=gcc
CFLAGS=-Wall
OUTPUT=libhunbin.a
OBJS=JH_SEARCH.o
INCLUDE=-I../include

all : $(OBJS) $(OUTPUT)

$(OUTPUT): $(OBJS)
	ar rv $(OUTPUT) $(OBJS)
	
%.o: %.c ../include/%.h
	$(CC) -c $(CFLAGS) $< $(INCLUDE) -o $@

clean:
	rm -f $(OBJS) $(OUTPUT)
