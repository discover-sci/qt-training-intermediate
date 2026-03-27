#include "widget.h"
#include "./ui_widget.h"
#include "colorpicker.h"
#include "QDebug.h"

Widget::Widget (QWidget *parent)
    : QWidget (parent),
      ui (new Ui::Widget) {
  ui->setupUi (this);

  auto* colorPicker = new ColorPicker{this};


  QObject::connect(colorPicker, &ColorPicker::colorChanged, this, [this](){
    qDebug() << "color changed";

  });

  ui->verticalLayout->addWidget(colorPicker);


}

Widget::~Widget () { delete ui; }
