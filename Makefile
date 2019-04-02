CC := g++
BLD_DIR := ./build
BIN_DIR := ./bin
SRC_DIR := ./src
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BLD_DIR)/%.o,$(SRC_FILES))
BIN_NAME := cpproxy
LDFLAGS := -lpthread
CPPFLAGS := $()
CXXFLAGS := -std=c++11

all: clean $(BIN_NAME)

$(BIN_NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LDFLAGS) -o $(BIN_DIR)/$(BIN_NAME)

$(BLD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $< -o $@ $(CPPFLAGS) $(CXXFLAGS)

clean:
	rm -rf $(BLD_DIR)/ $(BIN_DIR)/
	mkdir $(BLD_DIR)
	mkdir $(BIN_DIR)
