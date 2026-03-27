#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow (QWidget *parent)
    : QMainWindow (parent), ui (new Ui::MainWindow) {
  ui->setupUi (this);

  // prevent floating or moving if you want it fixed
  ui->toolBar->setMovable(true);        // set false to lock in place
  ui->toolBar->setFloatable(false);


  QObject::connect(ui->actionCut, &QAction::triggered, this, [this]() {
    ui->textEdit->cut();
  });

  QObject::connect(ui->actionPaste, &QAction::triggered, this, [this]() {
    ui->textEdit->paste();
  });

  QObject::connect(ui->actionUndo, &QAction::triggered, this, [this]() {
    ui->textEdit->undo();
  });

  QObject::connect(ui->actionRedo, &QAction::triggered, this, [this]() {
    ui->textEdit->redo();
  });

  QObject::connect(ui->actionCopy, &QAction::triggered, this, [this]() {
    ui->textEdit->copy();
  });

  QObject::connect(ui->actionAbout, &QAction::triggered, this, [this]() {
    QMessageBox::about(this, "This is just an info...", "The important message is: Qt is cool.");
  });

  QObject::connect(ui->actionAbout_Qt, &QAction::triggered, this, [this]() {
    QApplication::aboutQt();
  });

  QObject::connect(ui->actionQuit, &QAction::triggered, this, [this]() {
    this->statusBar()->showMessage("App will be killed ...");
    QTimer::singleShot(2000, this, &MainWindow::quitApp);
  });

}

MainWindow::~MainWindow () {
  delete ui;
}

void MainWindow::quitApp() {
  QApplication::quit();

}
