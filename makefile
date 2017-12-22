BUILD_DIR=./build
CXX=g++
.PHONY: all
CXX_FLAGS=-DJUMBO_SUDOKU
all: jumbo

srcs = $(wildcard *.cpp)
objs = $(srcs:%.cpp=$(BUILD_DIR)/%.o) 

jumbo: $(BUILD_DIR)/solver.o\
        $(BUILD_DIR)/inp.o\
        $(BUILD_DIR)/sudoku.o
	g++ -o $@ $^

$(BUILD_DIR)/%.o: %.cpp cell.hpp
	$(CXX) $(CXX_FLAGS) $(INCLUDES)   -c $< -o $@

.PHONY: clean

# $(RM) is rm -f by default
clean:
	$(RM) $(objs) jumbo

