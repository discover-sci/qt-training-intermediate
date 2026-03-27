#include "rockwidget.h"

#include <QApplication>

int main (int argc, char *argv[]) {
  QApplication a (argc, argv);
  Rockwidget rw = Rockwidget{nullptr}; // parent in Widget is nullptr by default, but you can specify it here as well
  rw.setWindowTitle("App from scratch");
  rw.show();


  return a.exec ();
}
