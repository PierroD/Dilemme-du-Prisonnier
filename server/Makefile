CC		:= gcc
CFLAGS	:= -Wall -Wextra -g -std=c99 

BUILD		:= build
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:= -lpthread
DOXYGENCONF = Doxyfile
ifeq ($(OS),Windows_NT)
EXECUTABLE	:= server.exe
SOURCEDIRS	:= $(SRC)
INCLUDEDIRS	:= $(INCLUDE)
LIBDIRS		:= $(LIB)
else
EXECUTABLE	:= server
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)
endif

CINCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
CLIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))

SOURCES		:= $(wildcard $(patsubst %,%/*.c, $(SOURCEDIRS)))
OBJECTS		:= $(SOURCES:.c=.o)

all: $(BUILD)/$(EXECUTABLE)

.PHONY: clean
clean:
	-$(RM) $(BUILD)/$(EXECUTABLE)
	-$(RM) $(OBJECTS)


run: all
	./$(BUILD)/$(EXECUTABLE)

documentation:
	-doxygen $(DOXYGENCONF)

$(BUILD)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(CINCLUDES) $(CLIBS) $^ -o $@ $(LIBRARIES)