CC=g++
OPTION=-std=c++11
INCLUDE=../../include/zstd/internal/type_traits/

all: type_traits_base_test.o cv_modifier_test.o

type_traits_base_test.o: type_traits_base_test.cc
	$(CC) $(OPTION) -I $(INCLUDE) type_traits_base_test.cc -o type_traits_base_test.o

cv_modifier_test.o: cv_modifier_test.cc
	$(CC) $(OPTION) -I $(INCLUDE) cv_modifier_test.cc -o cv_modifier_test.o

primary_type_category_test.o: primary_type_category_test.cc
	$(CC) $(OPTION) -I $(INCLUDE) primary_type_category_test.cc -o primary_type_category_test.o

signed_modifier_test.o: signed_modifier_test.cc
	$(CC) $(OPTION) -I $(INCLUDE) signed_modifier_test.cc -o signed_modifier_test.o	