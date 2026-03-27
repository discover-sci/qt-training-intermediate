#include "widget.h"
#include "./ui_widget.h"
#include "personmodel.h"

Widget::Widget (QWidget *parent)
    : QWidget (parent),
      ui (new Ui::Widget) {

  ui->setupUi (this);

  PersonModel* model = new PersonModel{this};
  ui->treeView->setModel(model);

  QObject::connect(ui->addRowButton,    &QPushButton::clicked, this, &Widget::onAddRow);
  QObject::connect(ui->removeRowButton, &QPushButton::clicked, this, &Widget::onRemoveRow);
  QObject::connect(ui->addChildButton,  &QPushButton::clicked, this, &Widget::onAddChild);

}

Widget::~Widget () {
  delete ui;
}

void Widget::onAddRow() {
  QModelIndex index = ui->treeView->selectionModel()->currentIndex();
  QAbstractItemModel* model = ui->treeView->model();

  // add a row only - we still need to add columns... see below
  // we add a new row under the same parent, just like index has got one, hence we use parent index.parent(), under which we add the row
  if (!model->insertRow(index.row() + 1, index.parent())) {
    return;
  }

  // add columns for a new row
  for(int column = 0; column < model->columnCount(index.parent());++column) {
    QModelIndex child = model->index(index.row() + 1, column, index.parent());
    model->setData(child, QVariant("[Empty Cell]"), Qt::EditRole);
  }


}
void Widget::onAddChild() {
  QModelIndex index = ui->treeView->selectionModel()->currentIndex();
  QAbstractItemModel* model = ui->treeView->model();

  // index becomes a parent, so we add row under index parent in insertRow() method
  if(!model->insertRow(0, index))
    return;
  //Loop through the colums to put in initial data.
  for(int column = 0; column < model->columnCount(index.parent()); ++column){
    QModelIndex child = model->index(0, column, index);
    model->setData(child, QVariant("[Empty Cell]"), Qt::EditRole);
  }

  // model->index(0, 0, index) is the current child under the index
  ui->treeView->selectionModel()->setCurrentIndex(model->index(0, 0, index), QItemSelectionModel::ClearAndSelect);

}

void Widget::onRemoveRow() {
  QModelIndex index = ui->treeView->selectionModel()->currentIndex();
  QAbstractItemModel* model = ui->treeView->model();
  model->removeRows(index.row(), 1, index.parent());
}

