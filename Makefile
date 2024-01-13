CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRC_DIR = src
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRCS))

TARGET = $(BIN_DIR)/nanovolts

all: build clean

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: build
build: $(TARGET)

.PHONY: clean
clean:
	rm -f $(BIN_DIR)/*.o
