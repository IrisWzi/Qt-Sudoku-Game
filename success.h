/*
 * File: difficulty.h
 * --------------
 * This file automatically generated for the success dialog.
 */

#ifndef SUCCESS_H
#define SUCCESS_H

#include <QDialog>

namespace Ui {
class Success;
}

class Success : public QDialog
{
    Q_OBJECT

public:
    explicit Success(QWidget *parent = 0);
    ~Success();

private:
    Ui::Success *ui;
};

#endif // SUCCESS_H
