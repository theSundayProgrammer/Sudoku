 #include "cell.hpp"
#include <exception>
#include <algorithm>
#include <vector>
#include <stdio.h>
using namespace std;
size_t cells[SUDOKU_SIZE][SUDOKU_SIZE];
size_t boxId(size_t row, size_t col)
{
	size_t k = row/3;
	size_t l = col/3;
	return  k*3 + l;	
}

bool legal(vector<cell> const& state,  cell const& cur)
{
	return  state.cend() == find_if(state.cbegin(), state.cend(), [&](cell const& c)
	{
		return  (c.val == cur.val && (c.row == cur.row || c.col == cur.col || c.box == cur.box));
			
	});

}
  bool is_legal(cell const& c)
  {
    for (size_t i=0; i<SUDOKU_SIZE; ++i)
      if (cells[c.row][i] == c.val)
        return false;
    for (size_t j=0; j<SUDOKU_SIZE; ++j)
      if (cells[j][c.col] == c.val)
        return false;
    auto box = boxId(c.row,c.col);
    size_t row = (box/3)*3;
    size_t col = (box%3)*3;
    for(size_t i =0; i<3; ++i)
      for(size_t j=0; j<3; ++j)
        if (cells[row+i][col+j]==c.val)
          return false;
    return true;
  }
cell const lastCell = { SUDOKU_SIZE, SUDOKU_SIZE, SUDOKU_SIZE, 0 };
class SudokuSolver{
  vector<cell> & currentState;
  public:
  SudokuSolver(vector<cell> & curState):
    currentState(curState){

      //populate cells using currenState
      for (auto const& c: currentState)
        cells[c.row][c.col] = c.val;
    }
  cell GetNextFreeCell() const
  {
    //Search for the first empty cell
    for (size_t i=0; i<SUDOKU_SIZE; ++i)
      for (size_t j=0; j<SUDOKU_SIZE; ++j)
        if(cells[i][j]==0)
        {
          cell c = {i , j, boxId(i,j), 0};
          return c;
        }
    return lastCell;
  }
  bool solve()
  {
    //find the first empty cell
    auto c= GetNextFreeCell( );
    if (c.row==9) return true;
    //fill the empty cell
    for (size_t val = 1; val <= SUDOKU_SIZE ; ++val)	{
      c.val = val;
      //bool found = legal(currentState,c);
      bool found = is_legal(c);
      if (found){
        currentState.push_back(c);
        cells[c.row][c.col] = c.val;
        if (solve()){
          return true;
        }else{
          currentState.pop_back();
          cells[c.row][c.col] = 0;
        }
      }
    }
    return false;
  }
};
bool ComputeSolution(vector<cell>& curState){
	SudokuSolver solver(curState);
	return solver.solve();
}
