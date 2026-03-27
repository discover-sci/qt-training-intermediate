#include "parentbutton.h"
#include <QDebug>
#include <QPushButton>

ParentButton::ParentButton (QWidget *parent) : QPushButton{ parent } {

}


void ParentButton::mousePressEvent(QMouseEvent *event) {
  qDebug() << "ParentButton mousePressEvent called.";
  QPushButton::mousePressEvent(event);
}
