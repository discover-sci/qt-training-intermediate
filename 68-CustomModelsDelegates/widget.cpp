#include "widget.h"
#include "./ui_widget.h"
#include "personmodel.h"
#include <QMessageBox>
#include <QInputDialog>
#include "persondelegate.h"

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

         // (fixed):
  PersonDelegate * listDelegate = new PersonDelegate(this);
  PersonDelegate * tableDelegate = new PersonDelegate(this);
  PersonDelegate * treeDelegate = new PersonDelegate(this);
  ui->listView->setItemDelegate(listDelegate);
  ui->tableView->setItemDelegate(tableDelegate);
  ui->treeView->setItemDelegate(treeDelegate);

  model = new PersonModel(this);

  ui->listView->setModel(model);
  ui->listView->setItemDelegate(listDelegate);

  ui->tableView->setModel(model);
  ui->tableView->setItemDelegate(tableDelegate);

  ui->treeView->setModel(model);
  ui->treeView->setItemDelegate(treeDelegate);


  QObject::connect(ui->addButton, &QPushButton::clicked, this, &Widget::onAddUser);
  QObject::connect(ui->removeButton, &QPushButton::clicked, this, &Widget::onRemoveUser);


}

Widget::~Widget () {
  delete ui;
}

void Widget::onAddUser() {

  bool ok;
  QString name = QInputDialog::getText(nullptr, "Names", tr("Person name:"), QLineEdit::Normal,"Type in name", &ok);

  if( ok && !name.isEmpty()){

    int age = QInputDialog::getInt(nullptr,"Person Age","Age",20,15,120);

    Person* person = new Person(name, "blue", age, this);
    this->model->addPerson(person);

  } else {
    QMessageBox::information(nullptr,"Failure","Must specify name and age");
  }

}

void Widget::onRemoveUser() {
  QModelIndex index = ui->listView->currentIndex();
  this->model->removePerson(index);

}
