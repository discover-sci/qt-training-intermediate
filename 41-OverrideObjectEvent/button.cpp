#include "button.h"
#include <QEvent>

Button::Button (QWidget *parent) : QPushButton{ parent } {}


bool Button::event(QEvent *event) {

  // Check for specific event types - only processed here, signal in the Widget class won't be called
  // returning true means event has been handled and it does not deserve any additional attention up the chain
  if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonDblClick) {
    qDebug() << "Button: mouse press or double-click detected";

    // event->accept();

    // return true;  // event handled stop further processing
    // or
    // return false;
  }

  // Always call the parent implementation for other cases
  return QPushButton::event(event);


}
