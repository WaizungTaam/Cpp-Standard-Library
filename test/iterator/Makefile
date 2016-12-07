CC=g++
OPTION=-std=c++11
INCLUDE=../../include/zstd/internal/iterator/

all: iterator_base_test.o iterator_traits_test.o iterator_operation_test.o iterator_adaptor_test.o

iterator_base_test.o: iterator_base_test.cc
	$(CC) $(OPTION) -I $(INCLUDE) iterator_base_test.cc -o iterator_base_test.o

iterator_traits_test.o: iterator_traits_test.cc
	$(CC) $(OPTION) -I $(INCLUDE) iterator_traits_test.cc -o iterator_traits_test.o

iterator_operation_test.o: iterator_operation_test.cc
	$(CC) $(OPTION) -I $(INCLUDE) iterator_operation_test.cc -o iterator_operation_test.o

iterator_adaptor_test.o: iterator_adaptor_test.cc
	$(CC) $(OPTION) -I $(INCLUDE) iterator_adaptor_test.cc -o iterator_adaptor_test.o