#include "widget.h"

#include <QApplication>

int main (int argc, char *argv[]) {
  QApplication a (argc, argv);
  Widget w;

  // set the stylesheet on the level of the whole app
  /*
  a.setStyleSheet("QPushButton{"
                                "color: rgb(255, 255, 0);"
                                "background-color: rgb(0, 0, 0);"
                                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
                                "}");
  */
  w.show ();
  return a.exec ();
}
