#include "chillineedit.h"
#include <QDebug>
#include "parentlineedit.h"
#include <QKeyEvent>

ChilLineEdit::ChilLineEdit (QWidget *parent)
    : ParentLineEdit{ parent } {


}


void ChilLineEdit::keyPressEvent(QKeyEvent *event) {
  qDebug() << "ChildLineEdit keyPressEvent called";

  // sign that event has been or not, accepted and parent is not going to handle it, unless we forward it to a parent
  qDebug() << "ChildLineEdit Accepted: " << event->isAccepted();


  qDebug() << "Child parentWidget is"
           << (parentWidget() ? parentWidget()->metaObject()->className() : "nullptr");

  event->ignore();

  if (event->key() == Qt::Key_Delete) {
    qDebug() << "Delete key was pressed";
    this->clear();
  } else {
    ParentLineEdit::keyPressEvent(event);
  }


}
