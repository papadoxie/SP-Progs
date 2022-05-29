#! Directories
SOURCE_DIR := source
INCLUDE_DIR := include
BIN_DIR := bin

#! Compiler Settings
CC := gcc
CFLAGS ?= -ggdb
CFLAGS := $(CFLAGS) -c
CFLAGS := $(CFLAGS) -Wall -Werror -Wextra
CFLAGS := $(CFLAGS) -I$(INCLUDE_DIR)
CFLAGS := $(CFLAGS) -MMD -MD -MP -ggdb
CFLAGS := $(CFLAGS) -fsanitize=address -fno-omit-frame-pointer

#! Linker Settings
LD := gcc
LDFLAGS :=
LDFLAGS := -fsanitize=address
LDPATH :=

#! Files
##? Sources
C_SRCS := $(wildcard $(SOURCE_DIR)/*.c)
##? Objects
OBJS := $(patsubst $(SOURCE_DIR)/%.c, $(BIN_DIR)/%.o, $(C_SRCS))

##? Headers
HDRS := $(wildcard $(INCLUDE_DIR)/*.h)
##? Dependencies
DEPS := $(patsubst $(SOURCE_DIR)/%.c, $(BIN_DIR)/%.d, $(C_SRCS))

##? Executable
BIN = $(BIN_DIR)/shell

#!Targets
.PHONY: all clean

all: $(BIN_DIR) $(BIN)

release: REMOVE_FLAGS := -ggdb -fsanitize=address -fno-omit-frame-pointer
release: CFLAGS := $(filter-out $(REMOVE_FLAGS), $(CFLAGS))
release: CFLAGS := $(CFLAGS) -O2
release: LDFLAGS := $(filter-out $(REMOVE_FLAGS), $(LDFLAGS))
release: all

$(BIN): $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@ $(LDPATH)

$(BIN_DIR):
	mkdir $(BIN_DIR)

-include $(DEPS)
$(BIN_DIR)/%.o: $(SOURCE_DIR)/%.c Makefile
	$(CC) $(CFLAGS) $< -o $@

clean:
	@$(RM) -rvf $(BIN_DIR)