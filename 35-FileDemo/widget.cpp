#include "widget.h"
#include "./ui_widget.h"
# include <QFileDialog>
#include <QMessageBox>

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  /* SAVE TextEdit int oa file on disk */
  QObject::connect(ui->savePushButton, &QPushButton::clicked, this, [this](){

    // Choose the file to save into
    QString filename = QFileDialog::getSaveFileName(this,"Save As");
    if( filename.isEmpty())
      return;

    QFile file(filename);

    // Open the file, else quit
    if( !file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
      return;

    // An interface as a conventient way to write into files
    QTextStream out(&file);
    out << ui->textEdit->toPlainText() << "\n";

    file.close();


  });


  QObject::connect(ui->selectPushButton, &QPushButton::clicked, this, [this](){
    QString filename = QFileDialog::getOpenFileName(this,"Choose File");
    if( filename.isEmpty())
      return;
    ui->sourceLineEdit->setText(filename);

  });




  QObject::connect(ui->copyPushButton, &QPushButton::clicked, this, [this](){

    QString srcFileName = ui->sourceLineEdit->text();
    QString destFileName = ui->destinationLineEdit->text();

    if( srcFileName.isEmpty() || destFileName.isEmpty())
      return;

    QFile file(srcFileName);
    if( file.copy(destFileName)) {
      QMessageBox::information(this,"Success","Copy successful");
    }else {
      QMessageBox::information(this,"Failure","Copy Failed");
    }
  });


  /* LOAD file content into TextEdit */
  QObject::connect(ui->loadPushButton, &QPushButton::clicked, this, [this](){

    // where we gonna save the content of a file
    QString  textContent;

    // Open the file from disk
    QString filename = QFileDialog::getOpenFileName(this,"Open File");

    if(filename.isEmpty())
      return;
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
      return;
    QTextStream in(&file);
    QString line = in.readLine();

    while(!line.isNull()){
      textContent.append(line);
      line = in.readLine();
    }
    file.close();
    ui->textEdit->clear();
    ui->textEdit->setPlainText(textContent);

  });


}

Widget::~Widget () { delete ui; }
