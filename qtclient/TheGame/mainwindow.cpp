#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap backGround(":/backgrounds/main-background.png");
    QPalette p = this->palette();
    p.setBrush(QPalette::Background, backGround);
    this->setPalette(p);
    this->resize(backGround.size());
}

MainWindow::~MainWindow()
{
    delete ui;
}
