#include "widget.h"
#include "./ui_widget.h"

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget), filter {new KeyboardFilter{this}} {
  ui->setupUi (this);

  if (ui->lineEdit) {
    ui->lineEdit->installEventFilter(this->filter);
  }

  QObject::connect(ui->removeFilterPpushButton, &QPushButton::clicked, this, [this](){
    if (ui->lineEdit && filter) {
      ui->lineEdit->removeEventFilter(this->filter);
    }
  });


}

Widget::~Widget () { delete ui; }
