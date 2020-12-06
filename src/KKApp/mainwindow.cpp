#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace KuaiKong::UI;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setMinimumSize(1280,720);
    this->setStyleSheet("background:#FFFFFF");

    ShortRadarWidget *radar = new ShortRadarWidget(this);
    radar->setGeometry(90,50,480,720);
    radar->show();

    LeoSurroundViewWidget *surround = new LeoSurroundViewWidget(this);
    surround->setGeometry(90,50,480,720);
    surround->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

