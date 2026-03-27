#include "widget.h"
#include "./ui_widget.h"
#include <QFileDialog>
#include <QMessageBox>

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  QObject::connect(ui->dirOrFilePushButton, &QPushButton::clicked, this, [this](){

    if (ui->listWidget->count() == 0) {
      QMessageBox::information(this,"Message","Empty list");
      return;
    }

    if (!ui->listWidget->selectedItems().isEmpty()) {
      QFileInfo fileInfo(ui->listWidget->currentItem()->text());
      if (fileInfo.isDir()) {
        QMessageBox::information(this,"Message","This is a Dir");
      } else if (fileInfo.isFile()) {
        QMessageBox::information(this,"Message","This is a File");
      } else {
        QMessageBox::information(this,"Message","This is something else");
      }
    } else {
      QMessageBox::information(this,"Message","Nothing selected");
      return;
    }
  });

  QObject::connect(ui->dirContentPushButton, &QPushButton::clicked, this, [this](){
    ui->listWidget->clear();

    QString dirPath = ui->lineEdit->text();
    if (dirPath.isEmpty())
      return;
    QDir dir(dirPath);

    // Get the list of files and directories in the folder
                                                                // filters                //sorting according to Name
    QList<QFileInfo> fileList = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries, QDir::Name | QDir::IgnoreCase);

    for( int i = 0 ; i < fileList.size() ; i++) {

          QString prefix;
          if(fileList.at(i).isFile()) {
            prefix = "FILE FOUND";
            qDebug() << prefix;
          }
          if(fileList.at(i).isDir()) {
            prefix = "DIRECTORY FOUND";
            qDebug() << prefix;
          }

      ui->listWidget->addItem(fileList.at(i).absoluteFilePath());
    }
  });

  QObject::connect(ui->selectDirPushButton, &QPushButton::clicked, this, [this]() {
    QString filename = QFileDialog::getExistingDirectory(this,"Choose Folder");
    if( filename.isEmpty())
      return;
    ui->lineEdit->setText(filename);
  });

  QObject::connect(ui->createDirPushButton, &QPushButton::clicked, this, [this](){
    //Create a dir if it doesn't exist already
    QString pathString = ui->lineEdit->text();
    if (pathString.isEmpty())
      return;
    QDir dir(pathString);
    if (!dir.exists()) {
      // Create the dir
      if(dir.mkpath(pathString)) {
        QMessageBox::information(this,"Message","Directory created");
      }
    } else {
      QMessageBox::information(this,"Message","Directory already exists");
    }
  });

  QObject::connect(ui->existenceDirPushButton, &QPushButton::clicked, this, [this](){
    //Check if a directory exists
    QString dirPath = ui->lineEdit->text();
    if (dirPath.isEmpty())
      return;

    QDir dir(dirPath);
    if (dir.exists()) {
      QMessageBox::information(this,"Message","Directory exists");
    } else {
      QMessageBox::information(this,"Message","Directory doesn't exist");
    }

  });




}

Widget::~Widget () { delete ui; }
