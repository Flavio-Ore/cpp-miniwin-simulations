# Compiler
CC = g++

# Flags
# -Ilib: Tells the compiler to look in the 'lib' folder for miniwin.h
# -lpthread -lX11: Libraries required for Miniwin on Linux
CFLAGS = -Ilib -Wall -std=c++11
LIBS = -lX11 -lpthread

# Directories
SRC_DIR = src
LIB_DIR = lib
BIN_DIR = bin

# The Miniwin library source
MINIWIN_SRC = $(LIB_DIR)/miniwin.cpp

# TARGETS
# usage: make frogger
# usage: make orbit

# Rule to compile Nonagon
nonagon:
	mkdir -p $(BIN_DIR)
	$(CC) $(SRC_DIR)/nonagon.cpp $(MINIWIN_SRC) -o $(BIN_DIR)/nonagon $(CFLAGS) $(LIBS)
	./$(BIN_DIR)/nonagon
	@echo "Build successful! Run with: ./bin/nonagon"

# Rule to compile Frogger
frogger:
	mkdir -p $(BIN_DIR)
	$(CC) $(SRC_DIR)/frogger.cpp $(MINIWIN_SRC) -o $(BIN_DIR)/frogger $(CFLAGS) $(LIBS)
	@echo "Build successful! Run with: ./bin/frogger"

# Rule to compile Orbit
orbit:
	mkdir -p $(BIN_DIR)
	$(CC) $(SRC_DIR)/orbit.cpp $(MINIWIN_SRC) -o $(BIN_DIR)/orbit $(CFLAGS) $(LIBS)
	@echo "Build successful! Run with: ./bin/orbit"

# Rule to clean up binaries
clean:
	rm -f $(BIN_DIR)/*