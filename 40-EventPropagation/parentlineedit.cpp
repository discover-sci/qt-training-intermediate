#include "parentlineedit.h"
#include <QKeyEvent>

ParentLineEdit::ParentLineEdit (QWidget *parent)
    : QLineEdit{ parent } {

}


void ParentLineEdit::keyPressEvent(QKeyEvent *event) {
  qDebug() << "ParentLineEdit keyPressEvent called";
  qDebug() << "ParentLineEdit Accepted: " << event->isAccepted();
  QLineEdit::keyPressEvent(event);
}
