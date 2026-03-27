#include "widget.h"
#include "./ui_widget.h"

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  // set the number of columns in QTreeWidget
  ui->treeWidget->setColumnCount(2);

  // add THE Root
  // QTreeWidgetItem* googleRoot = new QTreeWidgetItem(ui->treeWidget);  // one and only Google Inc root
  // googleRoot->setText(0,"Google Inc");    // 1st column
  // googleRoot->setText(1,"Head Quarters"); // 2nd column

  // // ***********************************************************************************
  // QTreeWidgetItem* googleIndia = new QTreeWidgetItem(); // create another node under Root
  // googleIndia->setText(0, "Google India");
  // googleIndia->setText(1, "Google India Branch");
  // googleRoot->addChild(googleIndia);                    // add it to root

  // QTreeWidgetItem* googleBangalore = new QTreeWidgetItem(); // create another node under Root
  // googleBangalore->setText(0, "Bangalore");
  // googleBangalore->setText(1, "Sales");
  // googleIndia->addChild(googleBangalore);

  // QTreeWidgetItem* googleMumbai = new QTreeWidgetItem();
  // googleMumbai->setText(0, "Mumbai");
  // googleMumbai->setText(1, "AI Research");
  // googleIndia->addChild(googleMumbai);

  // // ***********************************************************************************
  // QTreeWidgetItem* googleGhana = new QTreeWidgetItem();
  // googleGhana->setText(0, "Google Ghana");
  // googleGhana->setText(1, "Google Ghana AI Branch");
  // googleRoot->addChild(googleGhana);

  // QTreeWidgetItem* googleAkra = new QTreeWidgetItem();
  // googleAkra->setText(0, "Akra");
  // googleAkra->setText(1, "AI Research");
  // googleGhana->addChild(googleAkra);

  // automated and more organized manipulation
  auto googleRoot = addRootOrganization("Google Inc", "Headquarters");

  auto googleIndia = addChildOrganization(googleRoot, "Google India", "Google India Branch");
  this->addChildOrganization(googleIndia, "Mumbai", "AI Research");
  this->addChildOrganization(googleIndia, "Bangalore", "Sales");

  auto googleGhana = addChildOrganization(googleRoot,"Google Ghana", "Ghana Branch");
  this->addChildOrganization(googleGhana, "Akra", "AI");

}


QTreeWidgetItem* Widget::addRootOrganization(QString company, QString purpose){

  QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidget);
  item->setText(0,"Google Inc");
  item->setText(1,"Head Quarters");
  return item;
}

QTreeWidgetItem* Widget::addChildOrganization(QTreeWidgetItem *parent,QString branch, QString description){

  QTreeWidgetItem* item = new QTreeWidgetItem();
  item->setText(0, branch);
  item->setText(1, description);
  parent->addChild(item);
  return  item;

}

Widget::~Widget () { delete ui; }
