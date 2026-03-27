#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow (QWidget *parent)
    : QMainWindow (parent), ui (new Ui::MainWindow) {
  ui->setupUi (this);



  QObject::connect(ui->pushButton, &QPushButton::clicked, this, [this](){
    qDebug() << "Called slot.";
  });
}

MainWindow::~MainWindow () { delete ui; }
