/*
 * File: difficulty.cpp
 * --------------
 * This file automatically generated for the game mode dialog.
 */

#include "difficulty.h"
#include "ui_difficulty.h"

difficulty::difficulty(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::difficulty)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint |
                   Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
}

difficulty::~difficulty()
{
    delete ui;
}

//The slots sending signals to the mainwindow
void difficulty::on_easy_pressed()
{
    emit sendDiff(1);
}

void difficulty::on_medium_pressed()
{
    emit sendDiff(2);
}

void difficulty::on_difficult_pressed()
{
    emit sendDiff(3);
}

