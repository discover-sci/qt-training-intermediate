#include "widget.h"
#include "./ui_widget.h"
#include <QButtonGroup>

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  // First you create a group of buttons
  QButtonGroup *group = new QButtonGroup{this};
  group->addButton(ui->winCheckBox);
  group->addButton(ui->macCheckBox);
  group->addButton(ui->linuxCheckBox);
  group->setExclusive(true);

  QObject::connect(ui->winCheckBox, &QCheckBox::toggled, this, [](bool checked){
    if (checked) {
      qDebug() << "Win checked";
    }
  });

  QObject::connect(ui->beerCheckBox, &QCheckBox::toggled, this, [](bool checked){
    if (checked) {
      qDebug() << "Beer checked";
    }
  });

  QObject::connect(ui->setPushButton, &QCheckBox::clicked, this, [this](){
    if (ui->beerCheckBox->isChecked()) {
      qDebug() << "You are setting the defaults.";
      ui->beerCheckBox->setChecked(false);
      ui->juiceCheckBox->setChecked(false);
      ui->coffeeCheckBox->setChecked(true);
    }
  });

  QObject::connect(ui->grabPushButton, &QCheckBox::clicked, this, [this](){
    qDebug() << ui->beerCheckBox->isChecked();
    qDebug() << ui->juiceCheckBox->isChecked();
    qDebug() << ui->coffeeCheckBox->isChecked();
  });

}

Widget::~Widget () { delete ui; }
