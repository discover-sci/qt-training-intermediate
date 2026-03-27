#include "widget.h"
#include "./ui_widget.h"

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  // open the pixmap
  QPixmap myImage{":/images/bugs-bunny-hold-up-doc.gif"};
  ui->imageLabel->setPixmap(myImage.scaled(400,300));

}

Widget::~Widget () { delete ui; }
