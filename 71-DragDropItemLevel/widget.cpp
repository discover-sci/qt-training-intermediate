#include "widget.h"
#include "./ui_widget.h"

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  // this is meant to be a list model
  QStandardItemModel* model = new QStandardItemModel{this};

  //create items
  QStandardItem* item0 = new QStandardItem();
  item0->setDragEnabled(true);
  item0->setDropEnabled(true);
  item0->setText("Item0 [CAN DRAG] [CAN DROP]"); // or equivalently
                                                 // item0->setData("Item0 [CAN DRAG] [CAN DROP]", Qt::DisplayRole);

  QStandardItem* item1 = new QStandardItem();
  item1->setDragEnabled(true);
  item1->setDropEnabled(false);
  item1->setText("Item1 [CAN DRAG] [CAN'T DROP]");

  QStandardItem* item2 = new QStandardItem();
  item2->setDragEnabled(false);
  item2->setDropEnabled(true);
  item2->setText("Item2 [CAN'T DRAG] [CAN DROP]");

  QStandardItem* item3 = new QStandardItem();
  item3->setDragEnabled(false);
  item3->setDropEnabled(false);
  item3->setText("Item3 [CAN'T DRAG] [CAN'T DROP]");


  // Add the items to the model
  model->appendRow(item0);
  model->appendRow(item1);
  model->appendRow(item2);
  model->appendRow(item3);


  // List View can drag can drop
  ui->listView->setDragEnabled(true);
  ui->listView->setAcceptDrops(true);
  ui->listView->setModel(model);

  // Table View can drag, can't drop
  ui->tableView->setDragEnabled(true);
  ui->tableView->setAcceptDrops(false);
  ui->tableView->setModel(model);

  // Tree View can't drag, can drop
  ui->treeView->setDragEnabled(false);
  ui->treeView->setAcceptDrops(true);
  ui->treeView->setModel(model);
}

Widget::~Widget () { delete ui; }
