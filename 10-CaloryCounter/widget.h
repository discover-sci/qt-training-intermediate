#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"person.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget {
  Q_OBJECT

public:
  Widget (QWidget *parent = nullptr);
  ~Widget ();

  double time() const;
  void setTime(double newTime);

  void connectionManager();

private:
  Ui::Widget *ui;
  Person person_;
  double time_;
  double speed_;
  double caloryCount_;



private:
  Q_SIGNAL void caloryCountChanged();

private:
  Q_SLOT void calculateCalories();
  Q_SLOT void weightChanged(double weight);
  Q_SLOT void timeChaged(double time);
  Q_SLOT void speedChaged(double speed);


};
#endif // WIDGET_H
