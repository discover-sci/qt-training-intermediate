#include "widget.h"
#include "./ui_widget.h"
#include "dialog.h""

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  QObject::connect(ui->submitPushButton, &QPushButton::clicked, this, [this](){
    Dialog* dialog = new Dialog{this};
    int ret = dialog->exec();


  });



}

Widget::~Widget () { delete ui; }
