#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace KuaiKong::UI;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::white);

    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setMinimumSize(1280,720);
    this->setPalette(palette);

    InitOpenGL();

    LeoSurroundViewWidget *surround = new LeoSurroundViewWidget(this);
    surround->setGeometry(0,0,840,720);
    surround->show();

    ShortRadarWidget *radar = new ShortRadarWidget(this);
    radar->setGeometry(900,50,480,720);
    radar->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitOpenGL()
{
    if (!QGLFormat::hasOpenGL()){
        LOGE("no opengl");
    }
    else{
        LOGI("Opengl supportted.\n");
    }
}
