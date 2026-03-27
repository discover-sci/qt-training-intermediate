#include "mainwindow.h"
#include <QPushButton>
#include <QMessageBox>
#include <QApplication>
#include <QMenuBar>
#include <QAction>
#include <QMenu>
#include <QStatusBar>


MainWindow::MainWindow (QWidget *parent) : QMainWindow{ parent } {

  QPushButton *button = new QPushButton{"Start", this};
  button->setFixedSize(100, 20);


  this->setCentralWidget(button); // makes button be rendered through the whole main window
  this->statusBar()->show();

  QObject::connect(button, &QPushButton::clicked, this, [this](){
    this->buttonClicked();
    this->statusBar()->showMessage("You have clicked the button.", 3000);
  });

  this->quitAction = new QAction{"Quit"};

  QObject::connect(this->quitAction, &QAction::triggered, this, [this](){
    QApplication::quit();
  });

  /*!!!!!!!!!!!!!!!!!!!!!!*/
  /* IMPORTANT: QMainWindow already has got a menu bar defined and created, you access it via menuBar() method and manipulate it*/
  /*!!!!!!!!!!!!!!!!!!!!!!*/
  QMenu *fileMenu = this->menuBar()->addMenu("File");
  this->menuBar()->addMenu("Edit");
  this->menuBar()->addMenu("Window");
  this->menuBar()->addMenu("Tools");
  this->menuBar()->addMenu("Help");

  /*!!!!!!!!!!!!!!!!!!!!!!*/
  /* IMPORTANT: QMainWindow already has got a status bar defined and created, you access it via statusBar() method and manipulate it*/
  /*!!!!!!!!!!!!!!!!!!!!!!*/
  fileMenu->addAction(quitAction);

  // fileMenu = menuBar()->addMenu(tr("&File"));
  // fileMenu->addAction(newAct);
  // fileMenu->addAction(openAct);
  // fileMenu->addAction(saveAct);

  QFont buttonFont1("Times", 20, QFont::Bold);
  QPushButton *button1 = new QPushButton("Button1", this);
  button1->setMinimumSize(200, 100);
  button1->move(150,150);
  // button1->show();
  button1->setFont(buttonFont1);
  connect(button1, &QPushButton::clicked, this, [this]() {
    qDebug() << "Button clicked";
  });

  QFont buttonFont2("Times", 20, QFont::Bold);
  QPushButton *button2 = new QPushButton("Button2", this);
  button2->setMinimumSize(200, 100);
  button2->move(150,300);
  // button2->show();
  button2->setFont(buttonFont2);
  connect(button2, &QPushButton::pressed, this, [this]() {
    qDebug() << "Button pressed";

    int ret = QMessageBox::warning(this, "Just to warn you", "Watch out... It's coming...", QMessageBox::Ok | QMessageBox::Cancel);
    if (ret == QMessageBox::Ok) {
      qDebug() << "You have been careful ... good job.";
    } else if (ret == QMessageBox::Cancel) {
      qDebug() << "You have canceled me ... shame.";
    }



  });
  connect(button2, &QPushButton::released, this, [this]() {
    qDebug() << "Button released";
  });
  connect(button2, &QPushButton::clicked, this, [this]() {
    qDebug() << "Button clicked";
  });

}

void MainWindow::buttonClicked() {
  QMessageBox::information(this, "Just a message...","You have clicked the button.");

  QMessageBox messageBoxCustom{};
  messageBoxCustom.setMinimumSize(1000, 200);
  messageBoxCustom.setWindowTitle("Message Title");
  messageBoxCustom.setText("Something happened");
  messageBoxCustom.setInformativeText("Do you want to do something about it ?");
  messageBoxCustom.setIcon(QMessageBox::Critical);
  messageBoxCustom.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
  messageBoxCustom.setDefaultButton(QMessageBox::Cancel);
  int retMessageBox = messageBoxCustom.exec();
  qDebug() << retMessageBox;

  int retCritical = QMessageBox::critical(this, "message Title",
                                   "Something happened. Do you want to do something about it ?",
                                   QMessageBox::Ok|QMessageBox::Cancel);
  qDebug() << retCritical;



}


QSize MainWindow::sizeHint() const {
  return QSize{800,500};
}
