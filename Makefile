CC=gcc
CFLAGS=-Wall
OUTPUT=libfuncs.a
OBJS=test.o
INCLUDE=-I../include
all : $(OBJS) $(OUTPUT)
