#include "widget.h"
#include "./ui_widget.h"
#include "personmodel.h"
#include <QMessageBox>
#include <QInputDialog>

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  this->model = new PersonModel(this);

  ui->listView->setModel(model);
  ui->tableView->setModel(model);
  ui->treeView->setModel(model);

  // selection model should be the same for all, so that when you click the selection in one view, the others change accordingly
  ui->tableView->setSelectionModel(ui->listView->selectionModel());
  ui->treeView->setSelectionModel(ui->listView->selectionModel());

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
