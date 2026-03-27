#include "widget.h"
#include "./ui_widget.h"

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  // add an additional value into the list
  ui->comboBox->addItem("Venus");

  // if you want to edit current element and add it as a new item - not particulary useful in fact.
  // ui->comboBox->setEditable(true);

  QObject::connect(ui->listPushButton,&QPushButton::clicked, this, [this](){
    //
    qDebug() << "The combo box currently has " << QString::number(ui->comboBox->count()) << " items. They are :";
    for( int i =0; i < ui->comboBox->count() ; ++i) {
      qDebug() << "Index " << QString::number(i) << " : " << ui->comboBox->itemText(i);
    }
  });



  QObject::connect(ui->setPushButton,&QPushButton::clicked, this, [this](){
    // set the default item in the list, which has an index of 4
    ui->comboBox->setCurrentIndex(4);
  });


  QObject::connect(ui->capturePushButton,&QPushButton::clicked, this, [this](){
    qDebug() << "The currently selectd item in the combo is : " <<
        ui->comboBox->currentText() << " and the index is :" << QString::number(ui->comboBox->currentIndex());
  });
}

Widget::~Widget () { delete ui; }
