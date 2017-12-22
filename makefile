CXX=g++
.PHONY: all
CXX_FLAGS=-DJUMBO_SUDOKU
all: jumbo simple


simple: simple_solver.cpp inp.cpp sudoku.cpp cell.hpp
	$(CXX) -o $@ simple_solver.cpp inp.cpp sudoku.cpp


jumbo: jumbo_solver.cpp inp.cpp sudoku.cpp cell.hpp
	$(CXX) -o $@ $(CXX_FLAGS) jumbo_solver.cpp inp.cpp sudoku.cpp

