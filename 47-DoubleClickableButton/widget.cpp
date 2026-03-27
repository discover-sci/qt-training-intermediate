#include "widget.h"
#include "./ui_widget.h"
#include "doubleclickablebutton.h"

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  DoubleClickableButton* button = new DoubleClickableButton{this};
  button->setText("Click");
  ui->verticalLayout->addWidget(button);
  QObject::connect(button, &DoubleClickableButton::doubleClickedSignal, this, [this](){
    qDebug() << "Inside a slot: Button clicked with double click";
  });


}

Widget::~Widget () { delete ui; }
