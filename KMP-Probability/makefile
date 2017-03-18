PWD=.
project_name=KMP probability
TARGET=$(project_name)

exclude_dirs= include bin lib
CC=clang++
RM=rm -rf

exec=./bin
include=./include
lib=./lib

LIBS=-lm
CPPFLAGS= -g -Wall -Wno-unused -Wno-write-strings

SRCS=$(wildcard *.cpp)
OBJ=$(SRCS: .cpp=.o)

# LINK WITH link flags
$(TARGET): $(OBJ)
	$(CC) $(CPPFLAGS) -I$(include) -stdlib=libc++ -o $@ $^
	mv $@ $(exec)/

# COMPILE with compile flags
%.o : %.cpp
	$(CC) -std=c++11 -stdlib=libc++ -I$(include) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJ) $(exec)/$(TARGET)

all: $(TARGET)
	@echo "find sources:" $(SRCS)
	@echo "target has been complied!"

run: $(TARGET)
	$(exec)/$(TARGET)

init:
		@[ -d include ] || mkdir include
		@[ -d bin ] || mkdir bin
		@[ -d lib ] || mkdir lib
		@[ -d src ] || mkdir src
