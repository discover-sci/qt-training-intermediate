#include "widget.h"

#include <QApplication>
#include <QMessageBox>
#include <QResource>
#include <QFile>


int main (int argc, char *argv[]) {
  QApplication app (argc, argv);
  QApplication::setWindowIcon(QIcon(":/icons/title.png"));
  Widget w;
  w.show ();
  return app.exec();
}
