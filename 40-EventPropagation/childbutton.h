#ifndef CHILDBUTTON_H
#define CHILDBUTTON_H

#include "parentbutton.h"
#include <QObject>
#include <QWidget>

class ChildButton : public ParentButton {
  Q_OBJECT
public:
  ChildButton (QWidget *parent = nullptr);

  // QWidget interface
protected:
  void mousePressEvent(QMouseEvent *event);
};

#endif // CHILDBUTTON_H
