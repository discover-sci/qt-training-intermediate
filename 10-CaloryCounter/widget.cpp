#include "widget.h"
#include "./ui_widget.h"

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);
  this->connectionManager();

  this->person_.setWeight(ui->weightSpinBox->value());
  this->time_ = ui->timeSpinBox->value();
  this->speed_ = ui->speedSpinnBox->value();


  emit this->calculateCalories();

}

Widget::~Widget () { delete ui; }


void Widget::connectionManager() {
  QObject::connect(ui->speedSpinnBox, &QDoubleSpinBox::valueChanged,
                    this, &Widget::speedChaged);
  QObject::connect(ui->weightSpinBox, &QDoubleSpinBox::valueChanged,
                    this, &Widget::weightChanged);
  QObject::connect(ui->timeSpinBox, &QDoubleSpinBox::valueChanged,
                    this, &Widget::timeChaged);

  QObject::connect(this, &Widget::caloryCountChanged,
                    this, [this](){
                      ui->caloryCountLabel->setText(QString::number(this->caloryCount_));
                    });

}

double Widget::time() const {
  return this->time_;
}

void Widget::setTime(double newTime) {
  this->time_ = newTime;
}

void Widget::calculateCalories() {
    // CB = [0.0215 x KPH^3 - 0.1765 x KPH^2 + 0.8710 x KPH + 1.4577] x WKG x T
    this->caloryCount_= (
                        (0.0215 * (this->speed_ * this->speed_ * this->speed_))
                         - (0.1765 * (this->speed_ * this->speed_))
                         + (0.8710 * this->speed_) + 1.4577
                         ) * this->person_.weight() * this->time_;

    emit caloryCountChanged();
}

void Widget::weightChanged(double weight) {
  this->person_.setWeight(weight);
  this->calculateCalories();

}

void Widget::timeChaged(double time) {
  this->time_ = time;
  this->calculateCalories();
}

void Widget::speedChaged(double speed) {
  this->speed_ = speed;
  this->calculateCalories();
}
