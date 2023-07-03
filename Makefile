# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -lgtest -lgtest_main -pthread

# Source files
SRC = dtypes.cpp 1darray.cpp utils.cpp test_dtypes.cpp test_1darray.cpp main_test.cpp

# Output binary
OUT = test_runner

# Targets
all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT)
