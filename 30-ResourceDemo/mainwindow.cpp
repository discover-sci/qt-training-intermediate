#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMovie>

MainWindow::MainWindow (QWidget *parent)
    : QMainWindow (parent), ui (new Ui::MainWindow) {
  ui->setupUi (this);

  QMovie *movie = new QMovie(":/moving/images/bugs-bunny-hold-up-doc.gif");
  ui->imageLabel->setMovie(movie);
  movie->start();

}

MainWindow::~MainWindow () {
  delete ui;
}
