#include "widget.h"
#include "./ui_widget.h"
#include "personmodel.h"

Widget::Widget (QWidget *parent)
    : QWidget (parent),
      ui (new Ui::Widget) {

  ui->setupUi (this);

  PersonModel* model = new PersonModel{this};
  ui->treeView->setModel(model);


}

Widget::~Widget () {
  delete ui;
}
