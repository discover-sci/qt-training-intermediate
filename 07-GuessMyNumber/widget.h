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
  int secretNumber = 0;
  int guessNumber = 0;

private:
  Q_SLOT void onGuessButtonClicked();
  Q_SLOT void onResetButtonClicked();
};
#endif // WIDGET_H
