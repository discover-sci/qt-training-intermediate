#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget {
  Q_OBJECT

public:
  Widget (QWidget *parent = nullptr);
  ~Widget ();

private:
  Ui::Widget *ui;
  int count{5};

private:
  Q_SLOT void onPushButtonUp();
  // never used Q_SLOT void onPushButtonDown();
  Q_SLOT void onConsoleSignal(QString direction);
  Q_SIGNAL void consoleSignal(QString direction);
};
#endif // WIDGET_H
