#include "widget.h"
#include "./ui_widget.h"
#include "QMessageBox"

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);
  ui->progressBar->setValue(this->count*10);

  // Push button DOWN solved by separate slot method
  QObject::connect(ui->pushButtonUp, &QPushButton::clicked, this, &Widget::onPushButtonUp);

  // Slot method not used for pushed button
  //QObject::connect(ui->pushButtonDown, &QPushButton::clicked, this, &Widget::onPushButtonDown);

  // Push button DOWN solved by using lambda for a slot
  QObject::connect(ui->pushButtonDown, &QPushButton::clicked, this, [=](){
    if (this->count == 0) {
      QMessageBox::warning(this, "Value message", "Minimum value reached.");
      return;
    } else {
      --this->count;
      ui->textLabel->setText("Down");
      ui->lcdNumber->display(this->count);
      ui->horizontalSlider->setValue(this->count);
      ui->progressBar->setValue((this->count)*10);
      emit consoleSignal("down");
    }
  });

  // slider move, sends a new value
  QObject::connect(ui->horizontalSlider, &QSlider::sliderMoved, this, [this](int position){

    this->count = position;

    ui->lcdNumber->display(this->count);
    ui->progressBar->setValue(this->count*10);
    // qDebug() << position;
  });



  QObject::connect(this, &Widget::consoleSignal, this, &Widget::onConsoleSignal);


}

Widget::~Widget () { delete ui; }

void Widget::onPushButtonUp() {
  if (this->count == 10) {
    QMessageBox::warning(this, "Value message", "Maximum value reached.");
  } else {
    ++this->count;
    ui->textLabel->setText("Up");
    ui->lcdNumber->display(this->count);
    ui->horizontalSlider->setValue(this->count);
    ui->progressBar->setValue(this->count*10);
    emit consoleSignal("up");
  }
}

void Widget::onConsoleSignal(QString direction) {
  qDebug().noquote() << QString("You have clicked \"%1\"").arg(direction);
}
