#ifndef ROCKWIDGET_H
#define ROCKWIDGET_H

#include <QWidget>
#include <QLabel>

class Rockwidget : public QWidget {
  Q_OBJECT

public:
  explicit Rockwidget (QWidget *parent = nullptr);

private:
  QSize sizeHint() const;


private:
  Q_SLOT void buttonClicked();


};

#endif // ROCKWIDGET_H
