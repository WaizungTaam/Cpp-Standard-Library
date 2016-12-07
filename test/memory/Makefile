CC=g++
OPTION=-std=c++11
INCLUDE=../../include/zstd/internal/memory/

all: addressof_test.o temporary_buffer_test.o uninitialized_test.o allocator_test.o pointer_traits_test.o allocator_traits_test.o

addressof_test.o: addressof_test.cc
	$(CC) $(OPTION) -I $(INCLUDE) addressof_test.cc -o addressof_test.o

temporary_buffer_test.o: temporary_buffer_test.cc
	$(CC) $(OPTION) -I $(INCLUDE) temporary_buffer_test.cc -o temporary_buffer_test.o	

uninitialized_test.o: uninitialized_test.cc
	$(CC) $(OPTION) -I $(INCLUDE) uninitialized_test.cc -o uninitialized_test.o

allocator_test.o: allocator_test.cc
	$(CC) $(OPTION) -I $(INCLUDE) allocator_test.cc -o allocator_test.o

pointer_traits_test.o: pointer_traits_test.cc
	$(CC) $(OPTION) -I $(INCLUDE) pointer_traits_test.cc -o pointer_traits_test.o

allocator_traits_test.o: allocator_traits_test.cc
	$(CC) $(OPTION) -I $(INCLUDE) allocator_traits_test.cc -o allocator_traits_test.o