#include "widget.h"
#include <QApplication>
#include <QApplication>
#include <QStyleFactory>
#include <QStyle>

void setDarkMode() {
  qApp->setStyle(QStyleFactory::create("Fusion"));

  QPalette dark;
  dark.setColor(QPalette::Window, QColor(53,53,53));
  dark.setColor(QPalette::WindowText, Qt::white);
  dark.setColor(QPalette::Base, QColor(25,25,25));
  dark.setColor(QPalette::AlternateBase, QColor(53,53,53));
  dark.setColor(QPalette::ToolTipBase, Qt::white);
  dark.setColor(QPalette::ToolTipText, Qt::white);
  dark.setColor(QPalette::Text, Qt::white);
  dark.setColor(QPalette::Button, QColor(53,53,53));
  dark.setColor(QPalette::ButtonText, Qt::white);
  dark.setColor(QPalette::BrightText, Qt::red);

  qApp->setPalette(dark);
}

void setLightMode() {
  qApp->setStyle(QStyleFactory::create("Fusion"));
  qApp->setPalette(QApplication::style()->standardPalette());
}


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Widget w;
    // setLightMode();
    w.show();
    return a.exec();
}
