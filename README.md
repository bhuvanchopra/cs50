# cs50
It is a repository of all my programs written for solving problem sets in the CS50 course of Harvard University.

It is a C program that implements the Game of Fifteen.

The Game of Fifteen is a puzzle played on a square, two-dimensional board with numbered tiles that slide. 
The goal of this puzzle is to arrange the board’s tiles from smallest to largest, left to right, top to bottom,
with an empty space in board’s bottom-right corner, as shown below:

1      2      3      4

5      6      7      8

9      10     11     12

13     14     15      _

Although other configurations are possible, we shall assume that this game begins with the board’s tiles in reverse order,
from largest to smallest, left to right, top to bottom, with an empty space in the board’s bottom-right corner. If, however,
and only if the board contains an odd number of tiles (i.e., the height and width of the board are even), the positions of tiles
numbered 1 and 2 must be swapped, as shown below. The puzzle is solvable from this configuration.

15 14 13 12

11 10  9  8

 7  6  5  4

 3  1  2  _
