#include "keyboardfilter.h"
#include <QKeyEvent>

KeyboardFilter::KeyboardFilter (QObject *parent) : QObject{ parent } {}


bool KeyboardFilter::eventFilter(QObject *watched, QEvent *event) {
  // check for the validity of objects in the process
  if (!watched || !event)
    return false;

  // Filter out key press events
  if (event->type() == QEvent::KeyPress){

    //cast the event into the key type of Event
    const auto* keyEvent = static_cast<const QKeyEvent*>(event);
    // convert from string_view into QString
    QString s = QString::fromUtf8(KeyboardFilter::ALLOWED_NUMBERS.data(),static_cast<int>(KeyboardFilter::ALLOWED_NUMBERS.size()));

    if (keyEvent && s.contains(keyEvent->text())) {
      qDebug() << "Number filtered out:" << keyEvent->text();
      return true; // Event handled, no need to notify the destination
    }

  }

  //Call the parent implementation if false filtering
  return QObject::eventFilter(watched,event);

}
