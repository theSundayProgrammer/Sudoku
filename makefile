BUILD_DIR=./build
CXX=g++
.PHONY: all
CXX_FLAGS=-DJUMBO_SUDOKU
all: sudoku

srcs = $(wildcard *.cpp)
objs = $(srcs:%.cpp=$(BUILD_DIR)/%.o) 

sudoku: $(objs)
	g++ -o $@ $^

$(BUILD_DIR)/%.o: %.cpp cell.hpp
	$(CXX) $(CXX_FLAGS) $(INCLUDES)   -c $< -o $@

.PHONY: clean

# $(RM) is rm -f by default
clean:
	$(RM) $(objs) 

