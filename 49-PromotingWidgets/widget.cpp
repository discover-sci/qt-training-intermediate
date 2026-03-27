#include "widget.h"
#include "./ui_widget.h"
#include "watertank.h"
#include "indicator.h"

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  QObject::connect(ui->tank, &WaterTank::red, ui->indicator, &Indicator::activateRed);
  QObject::connect(ui->tank, &WaterTank::yellow, ui->indicator, &Indicator::activateYellow);
  QObject::connect(ui->tank, &WaterTank::green, ui->indicator, &Indicator::activateGreen);
}

Widget::~Widget () { delete ui; }
