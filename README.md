# Get516

A simple cli game wherein user will play to get cell valued 516 starting from cell valued 2 by moving vertically and horizontally as needed.

# About code

Gamestate struct is defined using typedef and is used to encapsulate game and in it the functions required to run the game are defined. A 4x4 grid is defined. When 2 cells of same number collide, they are merged to a single cell of doubled value and continues to happen so until a cell of value 516 forms. However, is all the cells are full and 516 cell is not formed yet, the game is lost and thus terminates.
 
# Guidelines to use the game

The code needs to be copied on any desired IDE and then can be debugged and run using gcc compiler. <br/>
Output window :<br/>

