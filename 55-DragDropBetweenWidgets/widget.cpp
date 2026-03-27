#include "widget.h"
#include "./ui_widget.h"
#include <QSplitter>
#include "container.h"



Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  auto * splitter = new QSplitter(this);

  splitter->addWidget(new Container(this));
  splitter->addWidget(new Container(this));

         //Add the splitter to the layout
  ui->verticalLayout->addWidget(splitter);


}

Widget::~Widget () { delete ui; }
