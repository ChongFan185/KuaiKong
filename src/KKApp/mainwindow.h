#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QApplication>
#include <QDialog>
#include <QMainWindow>
#include <QtOpenGL/QGL>
#include <QRect>
#include <QThread>
#include <iostream>
#include <unistd.h>
#include <stdio.h>

#include "libs/leobase/common_leo.h"
#include "UI/shortradarwidget.h"
#include "UI/leosurroundviewwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void InitOpenGL();

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
