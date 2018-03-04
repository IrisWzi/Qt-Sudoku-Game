/*
 * File: mainwindow.h
 * --------------
 * This file exports functions for the main window.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include "difficulty.h"
#include "success.h"
#include "quit.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /*
     * Constructor: MainWindow
     * ------------------------
     * The constructor set up the general ui, set the timer,
     * and connect signals and slots.
     */

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    /*
     * Slot: initGame
     * ----------------------------------------
     * This slot starts a new game.
     */

    void initGame();

    /*
     * Slot: setDifficulty
     * ----------------------------------------
     * This slot sets the difficulty of the game.
     */

    void setDifficulty(int i);

    /*
     * Slot: updateTime
     * ----------------------------------------
     * This slot updates the time.
     */

    void updateTime();

    /*
     * Slot: click_pb(num)
     * ----------------------------------------
     * This slot sets the value of the selected cell and
     * check if the game is successfully compeleted.
     */

    void click_pb(int num);

    /*
     * Slot: on_pb1_clicked
     * ----------------------------------------
     * The following slots corresponds to each button.
     */

    void on_pb1_1_clicked();

    void on_pb1_2_clicked();

    void on_pb1_3_clicked();

    void on_pb1_4_clicked();

    void on_pb1_5_clicked();

    void on_pb1_6_clicked();

    void on_pb1_7_clicked();

    void on_pb1_8_clicked();

    void on_pb1_9_clicked();

    /*
     * Slot: on_grid_cellPressed(Row, Column)
     * ----------------------------------------
     * This slot stores the position of the recently
     * pressed cell in the board.
     */

    void on_grid_cellPressed(int Row, int Column);

    /*
     * Slot: on_restart_released
     * ----------------------------------------
     * This slot checks if the user really wants to quit the game and
     * restarts the game.
     */

    void on_restart_released();

    /*
     * Slot: on_check_pressed, on_check_released
     * ----------------------------------------
     * These slots show the wrong cell when pressed and
     * return to original state when released.
     */

    void on_check_pressed();

    void on_check_released();

    /*
     * Slot: on_solution_clicked
     * ----------------------------------------
     * This slot displays the solution and stops the timer.
     */

    void on_solution_clicked();

    /*
     * Slot: on_pause_clicked
     * ----------------------------------------
     * This slot pauses or returns to the game.
     */

    void on_pause_clicked();

    /*
     * Slot: on_hint_pressed, on_hint_released
     * ----------------------------------------
     * These slots show the answer to the cell selected when pressed
     * and return to original state when released.
     */

    void on_hint_pressed();

    void on_hint_released();

private:
    Ui::MainWindow *ui;
    QTimer * timer;     //the timer
    QTime * timeRecord;     //the time record
    int row, col, diffi;        //the row and column of the cell selected and the difficulty of the game
    bool paused, quit, selected;    //if the game is paused/if the user has quitted the game/the any cell had been selected.
};

#endif // MAINWINDOW_H
