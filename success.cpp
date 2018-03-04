/*
 * File: success.cpp
 * --------------
 * This file automatically generated for the success dialog.
 */

#include "success.h"
#include "ui_success.h"

Success::Success(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Success)
{
    ui->setupUi(this);
}

Success::~Success()
{
    delete ui;
}
