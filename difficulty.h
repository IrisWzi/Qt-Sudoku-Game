/*
 * File: difficulty.h
 * --------------
 * This file automatically generated for the game mode dialog.
 */

#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include <QDialog>

namespace Ui {
class difficulty;
}

class difficulty : public QDialog
{
    Q_OBJECT

public:
    explicit difficulty(QWidget *parent = 0);
    ~difficulty();

//The slots for the difficulty selection push button.
private slots:
    void on_easy_pressed();

    void on_medium_pressed();

    void on_difficult_pressed();


signals:

void sendDiff(int);     //send the signal of the difficulty level

private:
    Ui::difficulty *ui;
     int diff;



};

#endif // DIFFICULTY_H
