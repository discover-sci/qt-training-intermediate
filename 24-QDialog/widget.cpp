#include "widget.h"
#include "./ui_widget.h"
#include "infodialog.h"

// #define MODAL
#define NONMODAL

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  QObject::connect(ui->pushButton, &QPushButton::clicked, this, &Widget::onPushButton);
}

Widget::~Widget () { delete ui; }

void Widget::onPushButton() {
  auto *infoDialog = new InfoDialog{this};

  /*Chose one of two options below*/

#if defined(MODAL)
  /**********************************************************************************************************************/
  /* MODAL WAY - you are in a mode and do not let anything else to happen until you finsih the job with current dialog */
  auto ret = infoDialog->exec();
  if (ret == QDialog::Accepted) {
    qDebug() << "Dialog accepted";
  } else if (ret == QDialog::Rejected) {
    qDebug() << "Dialog rejected"; }
  ui->positionLabel->setText(infoDialog->position());
  ui->osLabel->setText(infoDialog->favoriteOS());
  /**********************************************************************************************************************/
#endif

#if defined(NONMODAL)
  /**********************************************************************************************************************/
  /* NON-MODAL WAY. You have access back to the initiator of a dialog. */
  // when entering, disable the button, that made a Dialog to appear
  ui->pushButton->setEnabled(false);

  // take care of re-activating a button on a widget, so that you can again call the Dialog back
  // when Dialog finishes its job - send the signal to re-activate the push button on a widget
  connect(infoDialog, &QDialog::finished, this, [this, infoDialog](int result) {
    if (result == QDialog::Accepted) {
      qDebug() << "Dialog accepted";
    } else {
      qDebug() << "Dialog rejected"; }
    ui->pushButton->setEnabled(true);
    ui->positionLabel->setText(infoDialog->position());
    ui->osLabel->setText(infoDialog->favoriteOS());
  });

  // show the dialog in a non-modal way
  infoDialog->show();
  /**********************************************************************************************************************/
#endif


}


