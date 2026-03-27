#include "widget.h"
#include "./ui_widget.h"
#include "QDebug"
#include "QMessageBox"

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  // [static] QMetaObject::Connection QObject::connect(const QObject *sender, const char *signal, const QObject *receiver, const char *method, Qt::ConnectionType type = Qt::AutoConnection)

  QObject::connect(this->ui->myButton, &QPushButton::clicked, this, &Widget::buttonClicked);

}

Widget::~Widget () { delete ui; }

void Widget::buttonClicked() {
  qDebug() << "Button Clicked";
  QMessageBox::information( this, "Message for you", "Here you go.\n\nThis is a longer message so the box becomes larger." );
}
