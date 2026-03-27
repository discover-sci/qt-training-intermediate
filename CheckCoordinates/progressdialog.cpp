#include "progressdialog.h"
#include "ui_progressdialog.h"

ProgressDialog::ProgressDialog(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::ProgressDialog)
{
  ui->setupUi(this);
  setModal(true);
  setWindowTitle("Processing REST Calls");
}

ProgressDialog::~ProgressDialog() {
  delete ui;
}

void ProgressDialog::setProgress(int value) {
  ui->progressBar->setValue(value);
}

void ProgressDialog::setMaximum(int max) {
  ui->progressBar->setMaximum(max);
}

void ProgressDialog::setLabel(const QString &text) {
  ui->label->setText(text);
}
