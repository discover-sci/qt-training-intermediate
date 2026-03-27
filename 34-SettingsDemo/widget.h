#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QPushButton;

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
  QVector<QColor> colorList_;

private:
  void saveColor(QString key, QColor color);
  QColor loadColor(QString key);
  void setLoadedColor(QString key, int index, QPushButton *button);
};
#endif // WIDGET_H
