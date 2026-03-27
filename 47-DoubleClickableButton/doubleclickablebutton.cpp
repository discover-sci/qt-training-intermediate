#include "doubleclickablebutton.h"
#include <QDebug>

DoubleClickableButton::DoubleClickableButton (QWidget *parent)
    : QPushButton{ parent } {

}


void DoubleClickableButton::mouseDoubleClickEvent(QMouseEvent *event) {
  if (event) {
    qDebug() << "Inside an event: DoubleClickableButton double click event has been triggered.";
    emit doubleClickedSignal();
    QPushButton::mouseDoubleClickEvent(event);
  }
}
