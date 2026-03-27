#include "widget.h"
#include "./ui_widget.h"
#include <cstdlib>
#include <ctime>


Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  // attaching signals and slots
  QObject::connect(this->ui->guessButton, &QPushButton::clicked, this, &Widget::onGuessButtonClicked);
  QObject::connect(this->ui->resetButton, &QPushButton::clicked, this, &Widget::onResetButtonClicked);

  ui->messageLabel->setText("Start guessing");
  ui->guessButton->setDisabled(true);
  ui->spinBox->setDisabled(true);
}

Widget::~Widget () { delete ui; }

void Widget::onGuessButtonClicked() {

  this->guessNumber = ui->spinBox->value();

  if (this->guessNumber == this->secretNumber) {
    ui->messageLabel->setText("Congrats. You guessed the number: " + QString::number(this->secretNumber));
    ui->resetButton->setDisabled(false);
    ui->guessButton->setDisabled(true);
  } else {
      if (this->secretNumber < this->guessNumber) {
        ui->messageLabel->setText("The number is lower.");
      } else {
        ui->messageLabel->setText("The number is higher.");
      }
  }

  qDebug() << "Test Guess Button" << this->guessNumber;

}

void Widget::onResetButtonClicked() {

  std::srand(std::time(nullptr));
  this->secretNumber = rand() % 10 + 1;
  ui->resetButton->setDisabled(true);
  ui->guessButton->setDisabled(false);
  ui->messageLabel->setText("Start Guessing");

  ui->spinBox->setDisabled(false);

  qDebug() << "Test ResetButton. Random number generated: " << secretNumber;



}


