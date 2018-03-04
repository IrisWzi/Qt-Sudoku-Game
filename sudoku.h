/*
 * File: sudoku.h
 * --------------
 * This file exports functions for the Sudoku class. This class generate a
 * sudoku game.
 */


#ifndef SUDOKU_H
#define SUDOKU_H

#include <time.h>
#include <stdlib.h>
#include <string>
#include <set>
#include "sudokuboard.h"


class Sudoku{

public:
    enum gameType{ //the levels of difficulties
        EASY,
        MEDIUM,
        DIFFICULT,
    };

    /*
     * Constructor: Sudoku
     * ------------------------
     * The constructor is empty.
     */

    Sudoku();

    /*
     * Methods: initBoard
     * Usage: game.initBoard()
     * -------------------------
     * This method generates a playable sudoku board.
     */

    void initBoard();

    /*
     * Methods: getDiff
     * Usage: game.getDiff()
     * -------------------------
     * This method retreieves difficulty of the game
     */

    int getDiff();

    /*
     * Methods: setDifficulty
     * Usage: game.setDifficulty(i)
     * -------------------------
     * This method sets the difficulty of the game.
     */

    void setDifficulty(int i);

    /*
     * Methods: readOriginal
     * Usage: game.readOriginal(i, j)
     * -------------------------
     * This method reads the value of the element in the original board.
     */

    int readOriginal(int i, int j);

    /*
     * Methods: readRemoved
     * Usage: game.readRemoved(i, j)
     * -------------------------
     * This method reads the value of the element in the removed board.
     */

    int readRemoved(int i, int j);

    /*
     * Methods: readCurrent
     * Usage: game.readCurrent(i, j)
     * -------------------------
     * This method reads the value of the element in the current board.
     */

    int readCurrent(int i, int j);

    /*
     * Methods: set
     * Usage: game.set(row, col, num)
     * -------------------------
     * This method sets the value of the element in the current board to num.
     */

    void set(int row, int col, int num);

    /*
     * Methods: printBoard
     * Usage: game.printBoard(board);
     * -------------------------
     * This method prints the board to the console.
     * This method is no longer needed in the GUI implentation.
     */

//    void printBoard(SudokuBoard board);

    /*
     * Methods: success
     * Usage: game.success()
     * -------------------------
     * This method checks if the board is successfully solved.
     */

    bool success();

    /*
     * Methods: reset
     * Usage: game.reset()
     * -------------------------
     * This method resets the game by clearing all the boards
     * and generate new boards.
     */

    void reset();

    /*
     * Methods: quit
     * Usage: game.quit()
     * -------------------------
     * This method sets the current board to the original board.
     */

    void quit();



private:

    SudokuBoard board;      //the filled original board

    SudokuBoard rboard;     //the board with elements removed

    SudokuBoard cboard;     // the current board to be modified by the user

    gameType difficulty;        //the level of difficulty of the game

    /*
     * Methods: fill
     * Usage: fillElement(i, j), fillBox(row, col), fillDiagonal(), fillRemaining(i, j)
     * -------------------------
     * These methods fill the board according to the rule od sudoku game.
     */

    void fillElement(int i, int j);

    void fillBox(int row, int col);

    void fillDiagonal();

    bool fillRemaining(int i, int j);

    /*
     * Methods: solvable
     * Usage: ScanSolve(board), BackTrackSolve(board, startx, starty);
     * -------------------------
     * These methods checks if the board is solvable using scan solve and
     * backtracking respectively.
     */

//    bool ScanSolve(SudokuBoard board);

//    bool BackTrackSolve(SudokuBoard board, int startx = 0, int starty = 0);

//    bool solvable(SudokuBoard board);

    /*
     * Methods: SolveSudoku
     * Usage: game.SolveSudoku(board);
     * -------------------------
     * This method checks if the board is solvable using the brute-force way.
     */

    bool SolveSudoku(SudokuBoard board);

    /*
     * Methods: removal
     * Usage: newBoard = game.removal(board, type);
     * -------------------------
     * This method generate a removed board according to the game type.
     */

    SudokuBoard removal(SudokuBoard board, gameType type);

    /*
     * Methods: validRemove
     * Usage: game.validRemove(board, i, j);
     * -------------------------
     * This method checks if the board is valid if the element is removed.
     */

    bool validRemove(SudokuBoard board, int i, int j);

};

#endif // SUDOKU_H
