#include "button.h"
#include <QDebug>
#include <QMouseEvent>


Button::Button (QWidget *parent)
    : QPushButton{ parent } {

}


void Button::mousePressEvent(QMouseEvent *event) {
  qDebug() << "Button: Mouse press at: " << event->position();
  QPushButton::mousePressEvent(event);
}

void Button::mouseMoveEvent(QMouseEvent *event) {
  qDebug() << "Button: Mouse Move at: " << event->position();
  QPushButton::mouseMoveEvent(event);
}


void Button::mouseReleaseEvent(QMouseEvent *event) {
  qDebug() << "Button: Mouse Release at: " << event->position();
  QPushButton::mouseReleaseEvent(event);
}
