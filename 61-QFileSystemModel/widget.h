#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileSystemModel>

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
  QFileSystemModel* model;

private:
  Q_SLOT void addButtonClicked();
  Q_SLOT void removeButtonClicked();  //our Model for our View. These two are separated now. Unlike in QTreeWidget, where both are combined
};
#endif // WIDGET_H
