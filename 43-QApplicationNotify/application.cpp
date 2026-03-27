#include "application.h"
#include "widget.h"


Application::Application (int argc, char *argv[])
    : QApplication{argc, argv} {

}


bool Application::notify(QObject* destination, QEvent* event) {

  //Handle mouse events
  if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonDblClick) {

    qDebug() << "Application: mouse press or mouse double click detected";
    qDebug() << "Class name: " << destination->metaObject()->className();

    // Try to cast the destination object to our Widget type
    if (auto* widget = dynamic_cast<Widget*>(destination)) {
      qDebug() << "Cast successful";
    } else {
      qDebug() << "Cast failed";
    }

    return false;
  }
  return QApplication::notify(destination, event);
}
