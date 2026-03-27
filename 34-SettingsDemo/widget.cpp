#include "widget.h"
#include "./ui_widget.h"
#include <QColorDialog>
#include <QSettings>

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);


  for (int i=0; i < 9; ++i) {
    colorList_.append(Qt::gray);
  }


  QObject::connect(ui->savePushButton, &QPushButton::clicked, this, [this]() {
    this->saveColor("button_1", this->colorList_[0]);
    this->saveColor("button_2", this->colorList_[1]);
    this->saveColor("button_3", this->colorList_[2]);
    this->saveColor("button_4", this->colorList_[3]);
    this->saveColor("button_5", this->colorList_[4]);
    this->saveColor("button_6", this->colorList_[5]);
    this->saveColor("button_7", this->colorList_[6]);
    this->saveColor("button_8", this->colorList_[7]);
    this->saveColor("button_9", this->colorList_[8]);

  });

  QObject::connect(ui->loadPushButton, &QPushButton::clicked, this, [this](){
    this->setLoadedColor("button_1", 0, ui->pushButton_1);
    this->setLoadedColor("button_2", 0, ui->pushButton_2);
    this->setLoadedColor("button_3", 0, ui->pushButton_3);
    this->setLoadedColor("button_4", 0, ui->pushButton_4);
    this->setLoadedColor("button_5", 0, ui->pushButton_5);
    this->setLoadedColor("button_6", 0, ui->pushButton_6);
    this->setLoadedColor("button_7", 0, ui->pushButton_7);
    this->setLoadedColor("button_8", 0, ui->pushButton_8);
    this->setLoadedColor("button_9", 0, ui->pushButton_9);
  });

  QObject::connect(ui->pushButton_1, &QPushButton::clicked, this, [this](){
    QColor color = QColorDialog::getColor(this->colorList_[0], this, "Choose Background Color");
    if (color.isValid()) {
      // Save the color in the list in memory
      this->colorList_[0] = color;

      // Set background color to the button
      QString css = QString("background-color : %1").arg(color.name());
      ui->pushButton_1->setStyleSheet(css);
    }

  });

  QObject::connect(ui->pushButton_2, &QPushButton::clicked, this, [this](){

  });

  QObject::connect(ui->pushButton_3, &QPushButton::clicked, this, [this](){

  });

  QObject::connect(ui->pushButton_4, &QPushButton::clicked, this, [this](){

  });

  QObject::connect(ui->pushButton_5, &QPushButton::clicked, this, [this](){

  });

  QObject::connect(ui->pushButton_6, &QPushButton::clicked, this, [this](){

  });

  QObject::connect(ui->pushButton_7, &QPushButton::clicked, this, [this](){

  });

  QObject::connect(ui->pushButton_8, &QPushButton::clicked, this, [this](){

  });

  QObject::connect(ui->pushButton_9, &QPushButton::clicked, this, [this](){

  });

}

Widget::~Widget () {
  delete ui;
}

void Widget::setLoadedColor(QString key, int index, QPushButton *button) {
  // load from settings the color for the button
  QColor color = this->loadColor(key);

  // update the memory setting
  this->colorList_[index] = color;

  //set the color on the button widget
  QString css = QString{"background-color: %1"}.arg(color.name());
  button->setStyleSheet(css);
}


void Widget::saveColor(QString key, QColor color) {
  int red = color.red();
  int green = color.green();
  int blue = color.blue();

  QSettings settings("Telekom Slovenije", "SettingsDemo application", this);
  settings.beginGroup("ButtonColor");
  settings.setValue(key + "r", red);
  settings.setValue(key + "g", green);
  settings.setValue(key + "b", blue);
  settings.endGroup();
}

QColor Widget::loadColor(QString key) {
  int red;
  int green;
  int blue;
  QSettings settings("Telekom Slovenije", "SettingsDemo application", this);
  settings.beginGroup("ButtonColor");

  // value() should return a value for a specific setting via key, and we also provide default value of QVariant(0)
  // value() returns QVariant, means that we have to convert it to our desired type
  red = settings.value(key + "r", QVariant(0)).toInt();
  green = settings.value(key + "g", QVariant(0)).toInt();
  blue= settings.value(key + "b", QVariant(0)).toInt();

  settings.endGroup();
  return QColor(red, green, blue);
}
















