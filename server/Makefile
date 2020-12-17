CC		:= gcc
CFLAGS	:= -Wall -Wextra -g -std=c99 

BUILD		:= build
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:= -lpthread
DOXYGENCONF = Doxyfile
ifeq ($(OS),Windows_NT)
SERVER	:= server.exe
SOURCEDIRS	:= $(SRC)
INCLUDEDIRS	:= $(INCLUDE)
LIBDIRS		:= $(LIB)
else
SERVER	:= server
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)
endif

CINCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
CLIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))

SOURCES		:= $(wildcard $(patsubst %,%/*.c, $(SOURCEDIRS)))
OBJECTS		:= $(SOURCES:.c=.o)

all: $(BUILD)/$(SERVER)

.PHONY: clean
clean:
	-$(RM) $(BUILD)/$(SERVER)
	-$(RM) $(OBJECTS)


run: all
	./$(BUILD)/$(SERVER)

documentation:
	-doxygen $(DOXYGENCONF)

$(BUILD)/$(SERVER): $(OBJECTS)
	$(CC) $(CFLAGS) $(CINCLUDES) $(CLIBS) $^ -o $@ $(LIBRARIES)
