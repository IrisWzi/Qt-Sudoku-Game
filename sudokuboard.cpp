/*
 * File: sudokuboard.cpp
 * ----------------
 * This file implements the sudokuboard.h interface.
 */

#include "sudokuboard.h"

SudokuBoard::SudokuBoard()
{
    for (int i = 0; i < 9; i++){
        for (int j = 0; j <9; j++){
            board[i][j] = 0;
        }
    }
}

SudokuBoard::SudokuBoard(const SudokuBoard & other) {
    operator=(other);
}

SudokuBoard & SudokuBoard::operator=(const SudokuBoard & other) {
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            board[i][j] = other.get(i, j);
        }
    }
    return *this;
}

int SudokuBoard::get(int i, int j) const {
    return board[i][j];
}

void SudokuBoard::set(int i, int j, int e){
    board[i][j] = e;
}

void SudokuBoard::remove(int i, int j){
    board[i][j] = 0;
}

void SudokuBoard::clear(void) {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            board[i][j] = 0;
}

bool SudokuBoard::valid() const {       //check the blocks, rows, and columns
    return (IsValidHorizontal() && IsValidVertical() && IsValidBlocks());
}

bool SudokuBoard::isValid(int x, int y, int e) const {      //check if the number is valid in the current row, column, block
    if (CheckHorizontal(x, y, e) && CheckVertical(x, y, e) && CheckBlock(x, y, e))
        return true;
    else
        return false;
}

bool SudokuBoard::full() const {
    bool full = true;
    for (int i = 0; full && i < 9; i++)
        for (int j = 0; full && j < 9; j++)
            full = (board[i][j] != 0);
    return full;
}

bool SudokuBoard::CheckHorizontal(int x, int y, int e) const {
    bool valid = (board[x][y] == 0);
    for (int i = 0; valid && i < 9; ++i)
        valid = (board[i][y] != e);

    return valid;
}

bool SudokuBoard::CheckVertical(int x, int y, int e) const {
    bool valid = (board[x][y] == 0);
    for (int i = 0; i < 9 && valid; ++i)
        valid = (board[x][i] != e);
    return valid;
}

bool SudokuBoard::CheckBlock(int x, int y, int e) const {
    bool valid = (board[x][y] == 0);
    int startx, starty;
    startx = x - (x % 3);
    starty = y - (y % 3);
    for (int i = starty; valid && (i % 3 != 0 || i == starty); ++i)
        for (int j = startx; valid && (j % 3 != 0 || j == startx); ++j)
            valid = (board[j][i] != e);
    return valid;
}

bool SudokuBoard::IsValidHorizontal() const {
    bool elementOccured[10];
    bool valid = true;
    for (int i = 0; valid && i < 9; i++) {
        for (int j = 0; j < 10; ++j)
            elementOccured[j] = false;
        for (int j = 0; valid && j < 9; j++) {
            int curElem = board[j][i];
            valid = !elementOccured[curElem];
                elementOccured[curElem] = true;
        }
    }
    return valid;
}

bool SudokuBoard::IsValidVertical() const {
    bool elementOccured[10];
    bool valid = true;
    for (int i = 0; valid && i < 9; i++) {
        for (int j = 0; j < 10; j++)
            elementOccured[j] = false;
        for (int j = 0; valid && j < 9; j++) {
            int curElem = board[i][j];
            valid = !elementOccured[curElem];
            if (curElem != 0)
                elementOccured[curElem] = true;
        }
    }

    return valid;
}

bool SudokuBoard::IsValidBlocks() const {
    bool elementOccured[10];
    bool valid = true;
    for (int startX = 0; valid && startX < 9; startX += 3)
        for (int startY = 0; valid && startY < 9; startY += 3) {
            for (int j = 0; j < 10; ++j)
                elementOccured[j] = false;
            for (int i = startX; valid && (i % 3 != 0 || i == startX); i++)
                for (int j = startY; valid && (j % 3 != 0 || j == startY); j++) {
                    int curElem = board[j][i];
                    valid = !elementOccured[curElem];
                    if (curElem != 0)
                        elementOccured[curElem] = true;
                }
        }
    return valid;
}
