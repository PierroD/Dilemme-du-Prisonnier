CC		:= gcc
CFLAGS	:= -Wall -Wextra -g -std=c99

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:= -lpthread
DOXYGENCONF = Doxyfile
ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
SOURCEDIRS	:= $(SRC)
INCLUDEDIRS	:= $(INCLUDE)
LIBDIRS		:= $(LIB)
else
EXECUTABLE	:= client
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)
endif

CINCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
CLIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))

SOURCES		:= $(wildcard $(patsubst %,%/*.c, $(SOURCEDIRS)))
OBJECTS		:= $(SOURCES:.c=.o)

all: $(BIN)/$(EXECUTABLE)

.PHONY: clean
clean:
	-$(RM) $(BIN)/$(EXECUTABLE)
	-$(RM) $(OBJECTS)


run: all
	./$(BIN)/$(EXECUTABLE)

documentation:
	-doxygen $(DOXYGENCONF)

$(BIN)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(CINCLUDES) $(CLIBS) $^ -o $@ $(LIBRARIES)