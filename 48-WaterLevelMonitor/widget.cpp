#include "widget.h"
#include "./ui_widget.h"
#include "indicator.h"
#include "watertank.h"


Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  Indicator* indicator = new Indicator{this};
  WaterTank* tank = new WaterTank{this};
  ui->horizontalLayout->addWidget(tank);
  ui->horizontalLayout->addWidget(indicator);


  QObject::connect(tank, &WaterTank::red, indicator, &Indicator::activateRed);
  QObject::connect(tank, &WaterTank::yellow, indicator, &Indicator::activateYellow);
  QObject::connect(tank, &WaterTank::green, indicator, &Indicator::activateGreen);













  // connect(tank, &WaterTank::normal, indicator, &Indicator::activateNormal);
  // connect(tank, &WaterTank::warning, indicator, &Indicator::activateWarning);
  // connect(tank, &WaterTank::danger, indicator, &Indicator::activateDanger);

}

Widget::~Widget () { delete ui; }
