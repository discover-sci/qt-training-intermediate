#include "widget.h"
#include <QApplication>
#include <QFile >

QString readTextFile(QString path) {
  QFile file(path);
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QTextStream in(&file);
    return in.readAll();
  }
  return QString{};
}

int main (int argc, char *argv[]) {
  QApplication a (argc, argv);

  // read the CSS content using helper function
  QString cssContent = readTextFile(":/styles/styles.css");

  // apply the CSS content to
  if (cssContent.length() > 0)
    a.setStyleSheet(cssContent);

  Widget w;
  w.show ();
  return a.exec ();
}
