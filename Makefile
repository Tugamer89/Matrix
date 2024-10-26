CC = gcc
CFLAGS = -Ipingpong_lib

SRC = src
BIN_DIR = bin
DATA_DIR = data

MATRIX_EXEC = $(BIN_DIR)/matrix
MAIN_SRC = $(SRC)/matrix.c
MAIN_OBJ = $(BIN_DIR)/matrix.o

all: $(MATRIX_EXEC)

$(MATRIX_EXEC): $(MAIN_OBJ) | $(BIN_DIR)
	$(CC) -o $@ $(MAIN_OBJ)

$(MAIN_OBJ): $(MAIN_SRC) | $(BIN_DIR)
	$(CC) $(CFLAGS) -c -o $@ $(MAIN_SRC)

# Directories
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(DATA_DIR):
	mkdir -p $(DATA_DIR)

# Utilities
clean:
	rm -f $(BIN_DIR)/*.o $(MATRIX_EXEC)

.PHONY: all clean
