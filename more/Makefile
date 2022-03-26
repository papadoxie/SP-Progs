#! Directories
SOURCE_DIR := source/
INCLUDE_DIR := include/
BIN_DIR := bin/

#! Compiler Settings
CC := gcc
CFLAGS ?= -ggdb
CFLAGS := $(CFLAGS) -Wall -Werror -Wextra -Wpedantic
CFLAGS := $(CFLAGS) -I$(INCLUDE_DIR)

#! Linker Settings
LD := ld
LDFLAGS := 

#! Files
##? Sources
C_SRCS := $(wildcard $(SOURCE_DIR)/*.c)

##? Objects
OBJS := $(patsubst $(SOURCE_DIR)/%.c, $(BIN_DIR)/%.o, $(C_SRCS))

BIN = $(BIN_DIR)/more

.PHONY: all clean

all: $(BIN)

$(BIN): $(BIN_DIR) $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

$(BIN_DIR):
	mkdir $(BIN_DIR)

$(BIN_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -rvf $(BIN_DIR)