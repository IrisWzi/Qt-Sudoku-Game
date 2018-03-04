/*
 * File: sudokuboard.h
 * --------------
 * This file exports functions for the SudokuBoard class. This class generate a
 * 9*9 sudoku board using a 2D array.
 */

#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H


class SudokuBoard
{
public:

    /*
     * Constructor: SudokuBoard
     * Usage: SudokuBoard board;
     *        SudokuBoard board = SudokuBoard(other);
     * ------------------------
     * Creates a SudokuBoard object.  The default constructor sets all the
     * elements in the 9*9 board to 0.
     */

    SudokuBoard();

    SudokuBoard(const SudokuBoard & other);

    /*
     * Methods: =
     * Usage: SudokuBoard board = anotherBoard
     * -------------------------
     * This method overloads the = operator to copy the board.
     */

    SudokuBoard & operator=(const SudokuBoard & other);

    /*
     * Methods: get
     * Usage: board.get(i, j)
     * -------------------------
     * This method retreieves the value of the element.
     */

    int get(int i, int j) const;

    /*
     * Methods: set
     * Usage: board.set(i, j, e)
     * -------------------------
     * This method sets the value of the element to e.
     */

    void set(int i, int j, int e);

    /*
     * Methods: remove
     * Usage: board.remove(i, j)
     * -------------------------
     * This method sets the value of the element to 0.
     */

    void remove(int i, int j);

    /*
     * Methods: clear
     * Usage: board.clear()
     * -------------------------
     * This method sets the value of all the element to 0.
     */

    void clear();

    /*
     * Methods: valid
     * Usage: board.valid()
     * -------------------------
     * This method checks if the board is valid.
     */

    bool valid() const;

    /*
     * Methods: isValid
     * Usage: board.isValid(i, j,e)
     * -------------------------
     * This method checks if the board is valid after setting the element to value e.
     */

    bool isValid(int x, int y, int e) const;

    /*
     * Methods: full
     * Usage: board.full()
     * -------------------------
     * This method checks if all the elements in the board are nonzero.
     */

    bool full() const;


private:
    int board[9][9];    //The sudoku board

    /*
     * Methods: CheckHorizontal, CheckVertical, CheckBlock
     * Usage: board.CheckHorizontal(x, y, e), board.CheckVertical(x, y, e), board.CheckBlock(x, y, e)
     * -------------------------
     * These methods check if the coresponding block/row/column is valid if
     * the value of the element is set to e.
     */

    bool CheckHorizontal(int x, int y, int e) const;
    bool CheckVertical(int x, int y, int e) const;
    bool CheckBlock(int x, int y, int e) const;

    /*
     * Methods: IsValidHorizontal, IsValidVertical, IsValidBlocks
     * Usage: board.IsValidHorizontal(), board.IsValidVertical(), board.IsValidBlocks()
     * -------------------------
     * These methods check if the board is valid in each row, column, blocks.
     */

    bool IsValidHorizontal() const;
    bool IsValidVertical() const;
    bool IsValidBlocks() const;



};

#endif // SUDOKUBOARD_H
