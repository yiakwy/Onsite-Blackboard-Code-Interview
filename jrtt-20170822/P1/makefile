PWD=.
project_name=find_upper_right_corner_points
TARGET=$(project_name)

exclude_dirs= include bin lib
CXX=g++#clang++
CC=gcc
RM=rm -rf

exec=./bin
include=./include
lib=./lib

# sharedlib=$(PYLIBPATH)/.so#.dylib
# sharedlib=$(lib)/.so
PYLIBPATH=$(shell python-config --exec-prefix)/lib
test=$(SRCS_DIR)/main.cpp
app=$(test)

LIBS=

CFLAGS= -Wall -c
CPPFLAGS= -g -Wall -Wno-unused -Wno-write-strings

HEADERS=$(wildcard *.hpp) \
		$(wildcard $(include)/*.hpp)
ALLSRCS=$(wildcard *.cpp) \
        $(wildcard $(SRCS_DIR)/*.cpp)
CSRCS=$(wildcard $(SRCS_DIR)/*.c)
 SRCS=$(filter-out $(app), $(ALLSRCS))

SRCS_DIR=./src
# OBJ=$(SRCS: .cpp=.o)
 OBJ=$(patsubst %.cpp, %.o, $(SRCS))
COBJ=$(patsubst %.c, %.o, $(CSRCS))

# LINK WITH link flags
$(TARGET): $(OBJ) $(COBJ) $(test)
	$(CXX) -v $(CPPFLAGS) -I$(include) -std=c++11 -stdlib=libc++ $^ $(LIBS) -o $@
	mv $@ $(exec)/

buildshared: $(sharedlib)
	@python ./setup.py build

# COMPILE with compile flagsa
%.o : %.c
	$(CC)  -v -std=gnu99 -I$(include) $(CFLAGS) -c $< -o $@
	@echo $(GREEN) [INFO] $(COLOR_OFF) "compile C " $< "to obj"
%.o : %.cpp
	$(CXX) -v -std=c++11 -stdlib=libc++ -I$(include) $(CPPFLAGS) -c $< -o $@
	@echo $(GREEN) [INFO] $(COLOR_OFF) "compile CPP " $< "to obj"
$(sharedlib): $(SRCS)
	$(CXX) -v $(CPPFLAGS) -I$(include) -std=c++11 -stdlib=libc++ $^ -shared $(LIBS) -o $@
	sudo cp $@ /Library/Python/2.7/site-packages/

.PHONY: clean
clean:
	@echo $(GREEN) [INFO] $(COLOR_OFF) "find objs: " $(OBJ) $(COBJ)
	$(RM) $(OBJ) $(exec)/$(TARGET)

all: $(TARGET)
	@echo $(GREEN) [INFO] $(COLOR_OFF) "find sources: " $(SRCS)
	@echo $(GREEN) [INFO] $(COLOR_OFF) "target has been complied!"

lib: $(sharedlib)
	@echo $(GREEN) [INFO] $(COLOR_OFF) "make libs" $(sharedlib)

run: $(TARGET)
	$(exec)/$(TARGET)

COLOR_OFF='\033[0m'
GREEN='\033[0;32m'

headers=$(wildcard $(include)/*.h) \
		$(wildcard $(include)/*.hpp)

init:
		@echo $(GREEN) [INFO] $(COLOR_OFF) "headers are : " "$(HEADERS)"
		@echo $(GREEN) [INFO] $(COLOR_OFF) "srcs are" : "$(SRCS)"
		@[ -d include ] || mkdir include
		@for f in $(HEADERS); do \
			fn=$$(basename $$f); \
			[ -f `pwd`/include/$$fn ] || echo $(GREEN) [INFO] $(COLOR_OFF) moving $$f ...; \
			[ -f `pwd`/include/$$fn ] || mv $$f `pwd`/include/$$fn; \
		done
		@[ -d bin ] || mkdir bin
		@[ -d lib ] || mkdir lib
		@[ -d src ] || mkdir src
		@for f in $(SRCS); do \
			fn=$$(basename $$f); \
			[ -f `pwd`/src/$$fn ] || echo $(GREEN) [INFO] $(COLOR_OFF) moving $$f ...; \
			[ -f `pwd`/src/$$fn ] || mv $$f `pwd`/src/$$fn; \
		done

