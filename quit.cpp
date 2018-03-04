/*
 * File: quit.cpp
 * --------------
 * This file automatically generated for the quit dialog.
 */

#include "quit.h"
#include "ui_quit.h"

Quit::Quit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Quit)
{
    ui->setupUi(this);
}

Quit::~Quit()
{
    delete ui;
}
