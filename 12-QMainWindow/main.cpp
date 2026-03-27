#include <QApplication>
#include "mainwindow.h"

int main (int argc, char *argv[]) {
  QApplication a (argc, argv);
  MainWindow mainWindow{nullptr};
  mainWindow.setWindowTitle("Main Window Demo");
  mainWindow.show();


  return a.exec ();
}
