#include "widget.h"
#include "./ui_widget.h"
#include "button.h"

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  Button* button = new Button{this};
  button->setText("Click");

  QObject::connect(button, &QPushButton::clicked, this, [this](){
    qDebug() << "Clicked the button.";
  });


  ui->verticalLayout->addWidget(button);
}

Widget::~Widget () { delete ui; }
