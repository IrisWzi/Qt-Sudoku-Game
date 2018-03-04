/*
 * File: mainwindow.cpp
 * ----------------
 * This file implements the mainwindow.h interface.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sudoku.h"

Sudoku board;
QColor blue(230,243,255);
QColor darkBlue(153, 194, 255);
QColor red(255,153,153);
QColor white(255,255,255);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(717, 528);
    initGame();
    timer = new QTimer;
    timeRecord = new QTime(0, 0, 0);
    timer->start(1000);     //start the timer and set the format
    ui->Timer->setDigitCount(8);
    ui->Timer->setSegmentStyle(QLCDNumber::Flat);
    ui->Timer->display(timeRecord->toString("hh:mm:ss"));
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initGame() {
    ui->textBrowser->hide();
    ui->textBrowser->setFrameStyle(0);
    selected = false;
    difficulty * dif = new difficulty;      //initialize the game mode dialog
    connect(dif, SIGNAL(sendDiff(int)), this, SLOT(setDifficulty(int)));
    dif->show();
    paused = false;
    quit = false;
    if (dif->exec() == QDialog::Accepted){
        board.reset();
        ui->grid->setFixedSize(452, 452);
        QTableWidgetItem* Cell;
        for (int i = 0; i < 9; ++i) {       //fill the board
            for (int j = 0; j < 9; ++j) {
                Cell = ui->grid->item(i, j);
                if (board.readRemoved(i, j) != 0){
                    QString str = "";
                    str += '0' + board.readRemoved(i, j);
                    const QString cstr = str;
                    Cell->setText(cstr);
                    if (board.readRemoved(i, j))
                    {
                        Cell->setBackgroundColor(blue);
                    }
                }
            }
        }
    }
}

void MainWindow::setDifficulty(int i){
    diffi = i;
    board.setDifficulty(diffi);
    if (board.getDiff() == 1) {     //display difficulty level of the game
        ui->label->setText("Easy");
    } else if (board.getDiff() == 2) {
        ui->label->setText("Medium");
    } else {
        ui->label->setText("Difficult");
    }
}

void MainWindow::updateTime() {
    *timeRecord = timeRecord->addSecs(1);
    ui->Timer->display(timeRecord->toString("hh:mm:ss"));
}

void MainWindow::click_pb(int num){
    QTableWidgetItem* Cell = ui->grid->item(row, col);
    board.set(row, col, num);
    QString str = "";
    str += '0' + board.readCurrent(row, col);
    const QString cstr = str;
    Cell->setText(cstr);        //set the velue of the cell
    ui->grid->clearSelection();     //clear the selection
    if (board.success() && quit == false) {     //show the success dialog if game is compeleted
        Success * success = new Success;
        timer->stop();
        success->show();
    }
}


void MainWindow::on_grid_cellPressed(int Row, int Column)
{
    selected = true;
    row = Row;      //store the position of the cell selected
    col = Column;
}

void MainWindow::on_restart_released()
{
    timer->stop();
    ui->textBrowser->setVisible(true);      //hide the cover
    ui->grid->clearSelection();
    ui->label->clear();
    Quit * quitter = new Quit;
    if (quit == false){     //if the user has not seen the solution
        quitter->show();
    }
    if (quit == true || quitter->exec() == QDialog::Accepted){      //if the user decide to quit
        timer->stop();      //reset the timer
        timeRecord->setHMS(0,0,0);
        ui->Timer->display(timeRecord->toString("hh:mm:ss"));
        timer->start(1000);
        QTableWidgetItem* Cell;
        for (int i = 0; i < 9; ++i) {       //clear the board
            for (int j = 0; j < 9; ++j) {
                Cell = ui->grid->item(i, j);
                QString str = "";
                const QString cstr = str;
                Cell->setText(cstr);
                Cell->setBackgroundColor(white);
            }
        }
        initGame();
    } else {        //if the user decide not to quit
        ui->textBrowser->hide();
        timer->start();
    }
}

void MainWindow::on_check_pressed()
{
    QTableWidgetItem* Cell;
    Cell = ui->grid->item(row, col);
    ui->grid->clearSelection();
    for (int i = 0; i < 9; ++i) {       //check which cells are incorrect
        for (int j = 0; j < 9; ++j) {
            if (board.readCurrent(i, j) != 0 && board.readCurrent(i, j) != board.readOriginal(i, j)){
                Cell = ui->grid->item(i, j);
                Cell->setBackgroundColor(red);
            }
        }
    }
}

void MainWindow::on_check_released()
{
    QTableWidgetItem* Cell;
    for (int i = 0; i < 9; ++i) {       //return the modified cell to their original states
        for (int j = 0; j < 9; ++j) {
            if (board.readCurrent(i, j) != 0 && board.readCurrent(i, j) != board.readOriginal(i, j)){
                Cell = ui->grid->item(i, j);
                Cell->setBackgroundColor(white);
            }
        }
    }
}

void MainWindow::on_solution_clicked()
{
    quit = true;        //indicate the user has chosen solution
    board.quit();       //set the current board to be equal to the original board
    timer->stop();      //stop the timer
    QTableWidgetItem* Cell;
    for (int i = 0; i < 9; ++i) {       //refill the board
        for (int j = 0; j < 9; ++j) {
            Cell = ui->grid->item(i, j);
            QString str = "";
            str += '0' + board.readOriginal(i, j);
            const QString cstr = str;
            Cell->setText(cstr);
        }
    }
}


void MainWindow::on_pause_clicked()
{
    paused = !paused;
    const QString stop = "Pause";
    const QString back = "Return";
    if (paused) {
        ui->textBrowser->setVisible(true);      //display the cover
//        ui->grid->setVisible(false);
        ui->pause->setText(back);       //set the text label to Return
        timer->stop();
    } else {
        ui->textBrowser->hide();        //hide the cover
//        ui->grid->setVisible(true);
        ui->pause->setText(stop);       //set the text label to Pause
        timer->start();
    }
}

void MainWindow::on_hint_pressed()
{
    if (selected) {
        QTableWidgetItem* Cell = ui->grid->item(row, col);
        ui->grid->clearSelection();
        QString str = "";
        str += '0' + board.readOriginal(row, col);
        const QString cstr = str;
        Cell->setText(cstr);        //display the answer
        Cell->setBackgroundColor(darkBlue);     //set the color
    }
}

void MainWindow::on_hint_released()
{
    if (selected) {
        QTableWidgetItem* Cell = ui->grid->item(row, col);
        QString str = "";
        if (board.readCurrent(row, col) != 0) str += '0' + board.readCurrent(row, col);
        const QString cstr = str;
        Cell->setText(cstr);        //set the value to the current board
        Cell->setBackgroundColor(white);        // reset the color
    }
}


void MainWindow::on_pb1_1_clicked()
{
    click_pb(1);
}


void MainWindow::on_pb1_2_clicked()
{
    click_pb(2);
}

void MainWindow::on_pb1_3_clicked()
{
    click_pb(3);
}

void MainWindow::on_pb1_4_clicked()
{
    click_pb(4);
}

void MainWindow::on_pb1_5_clicked()
{
    click_pb(5);
}

void MainWindow::on_pb1_6_clicked()
{
    click_pb(6);
}

void MainWindow::on_pb1_7_clicked()
{
    click_pb(7);
}

void MainWindow::on_pb1_8_clicked()
{
    click_pb(8);
}

void MainWindow::on_pb1_9_clicked()
{
    click_pb(9);
}

