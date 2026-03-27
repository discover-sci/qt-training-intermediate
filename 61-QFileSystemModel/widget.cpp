#include "widget.h"
#include "./ui_widget.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QFileSystemModel>
#include <QObject>


Widget::Widget (QWidget *parent)
  : QWidget (parent),
    ui (new Ui::Widget) {

  ui->setupUi(this);

  this->model = new QFileSystemModel{this};
  this->model->setReadOnly(false); // enable changes

  /*
   * Sets the directory that is being watched by the model to newPath
   *  by installing a file system watcher on it. Any changes to files
   *  and directories within this directory will be reflected in the model.
   * */
  this->model->setRootPath(QDir::currentPath());

  // give the View its model
  ui->treeView->setModel(model);

  // for better view
  ui->treeView->setAlternatingRowColors(true);

  // get he QModelIndex element from model. in QTreeWidget, we had embedded QTreeWidgetItem elements, here QModelIndex elements are in model
  // and the View doesn't care about model...
  // So in a sense index() call does this: Give me a handle (QModelIndex) that points to the item representing the current directory.
  auto index = this->model->index(QDir::currentPath());

  ui->treeView->expand(index);
  ui->treeView->scrollTo(index);
  ui->treeView->resizeColumnToContents(0); // let the colums be the same size as the contet as they haveR


  QObject::connect(ui->addButton, &QPushButton::clicked, this, &Widget::addButtonClicked);
  QObject::connect(ui->removeButton, &QPushButton::clicked, this, &Widget::removeButtonClicked);
}


void Widget::addButtonClicked() {
  auto index = ui->treeView->currentIndex();
  if(!index.isValid()){
    return;
  }

  // get the dir name from user
  QString dirName = QInputDialog::getText(this, "Create Directory", "Directory name");

  if(!dirName.isEmpty()) {
    // make dir on index of type QModelIndex
    if(!model->mkdir(index, dirName).isValid()){
      QMessageBox::information(this, "Create Directory", "Failed to create the directory");
    }
  }
}

void Widget::removeButtonClicked() {
  auto index = ui->treeView->currentIndex();
  if(!index.isValid()){
    return;
  }

  bool ok;
  //Check to see if a dir or a file that you are deleting
  if(this->model->fileInfo(index).isDir()){
    ok = this->model->rmdir(index);
  } else {
    ok = this->model->remove(index);
  }

  if(!ok){
    QMessageBox::information(this, "Delete", QString("Failed to delete %1").arg(model->fileName(index)));
  }
}


Widget::~Widget () {
  delete ui;
}
