#include "childbutton.h"

ChildButton::ChildButton(QWidget *parent) : ParentButton{parent}{

}


void ChildButton::mousePressEvent(QMouseEvent *event) {
  qDebug() << "ChildButton mousePressEvent called.";

  // if we comment this, parent won't engage in its own mousePressEvent, and neither will a signal activate and so slot won't be called
  // the same in ParentButton... you simply cut the path that propagates all the way to a top level parent
  ParentButton::mousePressEvent(event);
}
