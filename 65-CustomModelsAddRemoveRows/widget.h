#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "personmodel.h"

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
  PersonModel* model;

private:
  Q_SLOT void onAddUser();
  Q_SLOT void onRemoveUser();

};
#endif // WIDGET_H
