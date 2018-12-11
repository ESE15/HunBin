CC=gcc
CFLAGS=-Wall
OUTPUT=libhunbin.a
OBJS=JH_SEARCH.o YB_SCRIPT.o
INCLUDE=-I../include

all : $(OBJS) $(OUTPUT)

$(OUTPUT): $(OBJS)
	ar rv $(OUTPUT) $(OBJS)
	
%.o: %.c ../include/%.h
	$(CC) -c $(CFLAGS) $< $(INCLUDE) -o $@

clean:
	rm -f $(OBJS) $(OUTPUT)
