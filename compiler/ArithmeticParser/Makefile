# author: Lei Wang (lwang11@mtu.edu)
# date: April 2017
# license: All Rights Reserved

PWD := .
project_name := arithemetic_parser
target := $(project_name)

CXX=clang++
CC=gcc
RM=rm -rf
AR=ar

EXEC=./bin
INCLUDE=./include
LIB=./lib
SRCS_DIR=./src

# configure platform
Uname := $(shell uname -s)
ifeq ($(Uname), Linux)
	OS := Linux
else ifeq ($(Uname), Darwin)
	OS := OSX
	OSX_Major_Version := $(shell sw_vers -productVersion | cut -f 1 -d .)
	OSX_Minor_Version := $(shell sw_vers -productVersion | cut -f 2 -d .)
endif

ifeq ($(OS), OSX)
	# device configure, computing OSX version
	# platform comparison checking ...
	# you might want to check this to find what happened : 
	OSX_GEQ_10_9 := $(shell [ $(OSX_Major_Version) -ge 10 ] && [ $(OSX_Minor_Version) -ge 9 ] && echo 1 )
	ifeq ($(OSX_Major_Version), 1)
		dysuffix := dylib
	else
		dysuffix := so
	endif
endif

PY_SYS_PREFIX=$(shell python-config --exec-prefix)
PYLIBPATH=$(PY_SYS_PREFIX)/lib
PYINCLUDEPATH=$(PY_SYS_PREFIX)/include

APP= $(shell echo $(PWD)/main.cpp)

APP_Obj= $(patsubst %.cpp,%.o,$(APP))

# MacOS Specific
BREW_DIR := /usr/local/Cellar

LINKFLAGS=
CPPFLAGS=
CFLAGS=
LINKFLAGS += -pthread -fPIC
CPPFLAGS += -pthread -fPIC
LDFLAGS := 
LIBRARY_DIRS := /usr/local/lib \
	$(BREW_DIR)/glog/0.3.4_1/lib \
	$(BREW_DIR)/boost/1.64.0_1/lib
				
PYLIBRARY_DIRS := $(LIBRARIES_DIR) \
	              $(PYLIBPATH) \
				  $(BREW_DIR)/boost-python/ \
				  
LIBRARIES := m glog
PYLIBRARIES := $(LIBRARIES) python2.7 boost_python boost_numpy

# If compile nornal cxx files
LIBS :=
LDFLAGS += $(foreach librarydir,$(LIBRARY_DIRS),-L$(librarydir)) \
		   $(foreach library,$(LIBRARIES),-l$(library))
LIBS += $(LDFLAGS)

INCLUDE_DIRS := /usr/local/include/
INCLUDE_DIRS += $(BREW_DIR)/glog/0.3.4_1/include \
				$(BREW_DIR)/boost/1.64.0_1/include
PYINCLUDE_DIRS := $(INCLUDE_DIRS) $(PYINCLUDEPATH)

CFLAGS += -Wall -c
COMMON_FLAGS= -g -Wall -Wno-unused -Wno-write-strings

# MODULES SUMMARY
ALL_MODULES :=

CPPFLAGS += -DREVISION=$(shell git rev-parse --short HEAD) \
			$(COMMON_FLAGS) \
			$(foreach includedir,$(INCLUDE_DIRS),-I$(includedir)) \
			$(XX_FLAGS)

ifeq ($(OS), OSX)
	# libraries configure
	# flags construction
	ifeq ($(CXX), g++)
		CPPFLAGS += -stdlib=libstdc++
		LINKFLAGS += -stdlib=libstdc++
	else ifeq ($(CXX), clang++)
		CPPFLAGS += -stdlib=libc++
		LINKFLAGS += -stdlib=libc++
	endif
endif

SRCS := $(shell find . -type d -maxdepth 1 \( -name "." -o -name "src" \) -exec bash -c "find {} -type f -name '*.cpp'" \;)
HEADERS := $(shell find . -type d -maxdepth 1 \( -name "." -o -name "include" \) -exec bash -c "find {} -type f -name '*.hpp'" \;)

# Moduel Spec

# Src Spec
COMMONCPP=
XX_Package_Src= $(filter-out $(APP) $(COMMONCPP),$(wildcard $(SRCS_DIR)/*.cpp))
 
# ObJ Spec
XX_Package_Obj= $(patsubst %.cpp, %.o, $(XX_Package_Src)) 
XX_FLAGS= -I$(INCLUDE)

$(target): parse

parse: $(XX_Package_Obj) $(APP_Obj)
	@echo $(GREEN) [INFO] $(COLOR_OFF) "building" $(YELLOW) $(target) $(COLOR_OFF) "package ... "
	@echo $(GREEN) [INFO] $(COLOR_OFF) "using sources:" $(XX_Package_Src)
	@for f in $(APP_Obj); do \
		fn=$$(basename $$f) ; \
	    tar=$$(echo $$fn | cut -d"." -f-1) ; \
		if [ -f $(SRCS_DIR)/$$fn ] || [ -f $(PWD)/$$fn ]; then \
		echo $(GREEN) [INFO] $(COLOR_OFF) "compiling taraget:" $(YELLOW) $$tar $(COLOR_OFF) "with XX_FLAGS:" $(XX_FLAGS) "..."; \
			 $(CXX) -v $(CPPFLAGS)  $(XX_FLAGS) -std=c++11 $(XX_Package_Obj) $$f $(LIBS) -o $$tar; \
		 	mv $$tar $(EXEC)/; \
		fi \
	done	
	@echo $(GREEN) [INFO] $(COLOR_OFF) "target built!"

buildshared: $(sharedlib)
	@python ./setup.py build

# COMPILE with compile flagsa
%.o : %.c
	@echo $(GREEN) [INFO] $(COLOR_OFF) "Compiling $@ ..."
	$(CC)  -v -std=gnu99  $(CFLAGS)-c $< -o $@
	@echo $(GREEN) [INFO] $(COLOR_OFF) "compiled C" $< "to obj"
%.o : %.cpp
	@echo $(GREEN) [INFO] $(COLOR_OFF) "Compiling $@ ..."
	$(CXX) -std=c++11  $(CPPFLAGS) -c $< -o $@
	@echo $(GREEN) [INFO] $(COLOR_OFF) "Compiled CPP" $< "to obj"

$(sharedlib): $(SRCS)
	$(CXX) -std=c++11 $(CPPFLAGS) $^ -shared $(LIBS) -o $@
	sudo cp $@ /Library/Python/2.7/site-packages/

.PHONY: clean
clean:
	@echo $(GREEN) [INFO] $(COLOR_OFF) "clean ..."
	$(RM) $(OBJ) $(exec)/$(TARGET)
	@echo $(GREEN) [INFO] $(COLOR_OFF) "cleaned up!"

all: $(target)
	@echo $(GREEN) [INFO] $(COLOR_OFF) "target has been complied!"

lib: $(sharedlib)
	@echo $(GREEN) [INFO] $(COLOR_OFF) "makeing libs" $(sharedlib)

run: $(target)
	$(EXEC)/$(target)

COLOR_OFF='\033[0m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'

echovar:
		@echo $(GREEN) [INFO] $(COLOR_OFF) "OS is" $(OS) "CPPFLAGS is" $(CPPFLAGS)
		@echo $(GREEN) [INFO] $(COLOR_OFF) "Get ArithmeticParser APP:" $(APP)
		@echo $(GREEN) [INFO] $(COLOR_OFF) "Get ArithmeticParser unfiltered srcs:  " $(wildcard $(SRCS_DIR)/*.cpp)
		@echo $(GREEN) [INFO] $(COLOR_OFF) "Get ArithmeticParser filtered srcs: " $(XX_Package_Src)
		@echo $(GREEN) [INFO] $(COLOR_OFF) "Get ArithmeticParser filtered objs: " $(patsubst %.cpp, %.o, $(XX_Package_Src))
		@echo $(GREEN) [INFO] $(COLOR_OFF) "GET ArithmeticParser local headers dirs : " $(XX_FLAGS)
init:
		@echo $(GREEN) [INFO] $(COLOR_OFF) "Initializing ..."
		@echo $(GREEN) [INFO] $(COLOR_OFF) "Get SRCS:\n" $(foreach file,$(SRCS),$(file)"\n")
		@echo $(GREEN) [INFO] $(COLOR_OFF) "Get HEADERS:\n" $(foreach file,$(HEADERS)/,$(file)"\n")
		@[ -d include ] || mkdir include
		@for f in $(HEADERS); do \
			fn=$$(basename $$f); \
			fndir="$$(dirname $$f | cut -d"/" -f3-)"; \
			[ -f `pwd`/include/$$fndir/$$fn ] || ( echo $(GREEN) [INFO] $(COLOR_OFF) moving $$f ...&& mkdir -p `pwd`/include/$$fndir && echo $$f `pwd`/include/$$fndir/$$fn ) ; \
		done
		@[ -d bin ] || mkdir bin
		@[ -d lib ] || mkdir lib
		@[ -d src ] || mkdir src
		@for f in $(SRCS); do \
			fn=$$(basename $$f); \
			fndir="$$(dirname $$f | cut -d"/" -f3-)"; \
			flag=0; \
			for app in $(APP); do \
				if [ $$app == $$f ]; then \
				echo $(GREEN) [INFO] ${COLOR_OFF} "skip app:" $$app; \
					flag=1; \
				fi; \
			done; \
			if [ $$flag -eq 0 ]; then \
				[ -f `pwd`/src/$$fndir/$$fn ] || (echo $(GREEN) [INFO] $(COLOR_OFF) moving $$f ... && mkdir -p `pwd`/src/$$fndir && echo $$f `pwd`/src/$$fndir/$$fn ); \
			fi \
		done

