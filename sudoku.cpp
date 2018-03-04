/*
 * File: sudoku.cpp
 * ----------------
 * This file implements the sudoku.h interface.
 */

#include "sudoku.h"
#include "random.h"
#include "ctype.h"
#include <iostream>
#include <string>
#include "sudokuboard.h"

using namespace std;

Sudoku::Sudoku(){
}

void Sudoku::initBoard(){
    fillDiagonal();     //fill the board
    fillRemaining(0, 3);
    rboard = removal(board, difficulty);        //remove the elements
    cboard = rboard;
}

int Sudoku::getDiff() {
    if (difficulty == EASY) return 1;
    if (difficulty == MEDIUM) return 2;
    if (difficulty == DIFFICULT) return 3;
    return -1;
}

int Sudoku::readOriginal(int i, int j){
    return board.get(i, j);
}

int Sudoku::readRemoved(int i, int j){
    return rboard.get(i, j);
}

int Sudoku::readCurrent(int i, int j){
    return cboard.get(i, j);
}

void Sudoku::set(int row, int col, int num){
    if (row >=0 && row <=8 && col >=0 && col <=8 && num >=1 && num <=9 &&
            board.get(row, col) != cboard.get(row, col)) {      //check if the position is valid and the element is empty or wrong
        cboard.set(row, col, num);
        }
}


void Sudoku::setDifficulty(int i){
    switch (i){
    case 1 : difficulty = EASY; break;
    case 2: difficulty = MEDIUM; break;
    case 3: difficulty = DIFFICULT; break;
    default: difficulty = MEDIUM;
    }
}

void Sudoku::fillDiagonal(){
    fillBox(0, 0);  //fill the three diagonal blocks
    fillBox(3, 3);
    fillBox(6, 6);
}

void Sudoku::fillElement(int i, int j){
    while(true){
        int num = randomInteger(1, 9);
        if (board.get(i, j) == 0 && board.isValid(i, j, num)) {     //fill all the empty elements and check for validity
            board.set(i, j, num);
            break;
    }
    }
}

void Sudoku::fillBox(int row, int col){
    for (int i = 0; i<3; i++){
        for (int j = 0; j<3; j++){
            fillElement(row+i, col+j);
        }
    }
}


bool Sudoku::fillRemaining(int i, int j) {
    if (j>=9 && i<8){
        i = i + 1;
        j = 0;
    }
    if (i>=9 && j>=9) return true;
    if (i < 3){
        if (j < 3) j = 3;
    } else if (i < 6){
        if (j==(int)(i/3)*3)
            j =  j + 3;
    } else{
        if (j == 6) {
            i = i + 1;
            j = 0;
            if (i>=9)
                return true;
        }
    }
    for (int num = 1; num<=9; num++) {
        if (board.isValid(i, j, num)){
            board.set(i, j, num);
            if (fillRemaining(i, j+1))
                return true;
            board.remove(i, j);
        }
    }
    return false;
}

bool Sudoku::SolveSudoku(SudokuBoard board){
    if (!board.full())
        return true;
    for (int row = 0; row < 9; row++){
        for (int col = 0; col < 9; col++){
            if (board.get(row, col) == 0){
                for (int num = 1; num <= 9; num++){
                    if (board.isValid(row, col, num)){
                        board.set(row, col, num);       //set the number in turn
                        if (SolveSudoku(board))     //check if the input is valid
                            return true;
                        board.remove(row, col);     //if the number is not valid, delete it
                    }
                }
            }
        }
    }
    return false;
}

SudokuBoard Sudoku::removal(SudokuBoard board, gameType type){
    SudokuBoard newBoard = board;       //construct a new board
    int numRemove;
    switch (type){      //decide how many elements are to be removed based on the difficulty
    case EASY: numRemove = randomInteger(35, 40); break;
    case MEDIUM: numRemove = randomInteger(45, 50); break;
    case DIFFICULT: numRemove = randomInteger(55, 60); break;
    }
    for (int i = 0; i < numRemove; i++) {
        while (true) {
            int row = randomInteger(0, 8);      //randomly generate the position
            int col = randomInteger(0, 8);
            if (newBoard.get(row, col) != 0 && validRemove(newBoard, row, col)) {       //if the elements has not been removed
                newBoard.remove(row, col);
                break;
            }
        }
    }
    return newBoard;
}


bool Sudoku::validRemove(SudokuBoard board, int i, int j) {
    board.remove(i, j);
    if (SolveSudoku(board)) return true;
    return false;
}


bool Sudoku::success(){
    if (cboard.full() && cboard.valid()) return true;       //if the board is filled and valid, the game is successfully compeleted
    return false;
}

void Sudoku::reset() {
    board.clear();      //clear the three boards
    rboard.clear();
    cboard.clear();
    initBoard();
}

void Sudoku::quit() {
    cboard = board;     //set the current board to the original board
}

//the following functions are no longer used

//void Sudoku::printBoard(SudokuBoard board){
//    cout<<"------------------------------------"<<endl;
//    for (int i = 0; i < 9; i ++){
//        cout<<"| ";
//        for (int j = 0; j < 9; j++){
//            cout<<board.get(i, j)<<"  ";
//            if (j ==2 || j==5 || j==8) cout<<"|  ";
//        }
//        cout<<endl;
//        if (i ==2 || i==5 || i==8) cout<<"------------------------------------"<<endl;
//        else  cout<<"- - - - - - - - - - - - - - - - - - "<<endl;
//    }
//}

//bool Sudoku::solvable(SudokuBoard board){
//    SudokuBoard copy = board;
//    printBoard(copy);
//    bool solved = ScanSolve(copy);
//    cout<<"solved?"<<solved<<endl;
//    if (!solved)
//        solved = BackTrackSolve(copy);
//    cout<<"solved?"<<solved<<endl;
//    return solved;
//    return false;

//}

//bool Sudoku::ScanSolve(SudokuBoard board) {
//    bool found = board.valid();
//    int numPossible;
//    bool possibleSolutions[9][9][10];
//    for (int y = 0; y < 9; ++y)
//        for (int x = 0; x < 9; ++x) {
//            possibleSolutions[x][y][0] = false;
//            for (int e = 1; e < 10; ++e)
//                possibleSolutions[x][y][e] = true;
//        }
//    while (!board.full() && found) {
//        found = false;
//        for (int y = 0; y < 9; ++y)
//            for (int x = 0; x < 9; ++x) {
//                numPossible = 0;
//                for (int e = 1; e < 10; ++e) {
//                    if (possibleSolutions[x][y][e]) {
//                        possibleSolutions[x][y][e] = board.isValid(x, y, e);
//                        if (possibleSolutions[x][y][e])
//                            ++numPossible;
//                    }
//                }
//                if (numPossible == 1) {
//                    for (int e = 1; e < 10; ++e)
//                        if (possibleSolutions[x][y][e])
//                            board.set(x, y, e);
//                    found = true;
//                }
//            }
//    }
//    return board.full();
//}

//bool Sudoku::BackTrackSolve(SudokuBoard board, int startx, int starty) {
//    bool solved = board.full();
//    bool foundzero = false;
//    int x = startx, y;
//    for (y = starty; !solved && !foundzero && y < 9; ++y) {
//        for (x = startx; !foundzero && x < 9; ++x)
//            foundzero = (board.get(x, y) == 0);
//        startx = 0;
//    }
//    x--;
//    y--;
//    if (!solved && foundzero) {
//        for (int e = 1; e < 10 && !solved; ++e)
//            if (board.isValid(x, y, e)) {
//                board.set(x, y, e);
//                if (BackTrackSolve(board, x + 1, y))
//                    solved = true;
//                else
//                    board.remove(x, y);
//            }
//    }

//    return solved;
//}

