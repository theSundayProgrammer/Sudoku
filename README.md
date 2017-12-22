Sudoku Solve
======
The make file builds two executables simple and jumbo. Simple is a Sudoku solver for the standard (3 * 3) * (3 * 3) Sudoku. Jumbo is essentially a solver for [Samurai sudoku](http://www.samurai-sudoku.com/) 

A sample input file is simple.txt. Essentially the appliation expects 81 characters between '1' and '9', and '.' to indicate blank. All other charachters are ignored and may be used to improve human readability.
The jumbo application expects a 21 * 21 matrix with a similar syntax as shown in the sample 'jumbo.txt'


The solver is a simple depth first algortithm. The difference between the two applications is in the utilities that solver uses.
Admittedly the code contains duplication whose avoidance could have saved a few hours of debugging.

