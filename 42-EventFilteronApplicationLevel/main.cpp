#include "mainwindow.h"

#include <QApplication>
#include "filter.h"

int main (int argc, char *argv[]) {
  QApplication a (argc, argv);
  MainWindow w;

  auto filter = new Filter(&w); // &w is a pointer to its parent
  a.installEventFilter(filter);


  w.show ();
  return a.exec ();
}
