#include "infodialog.h"
#include "ui_infodialog.h"
#include <QAbstractButton>

InfoDialog::InfoDialog (QWidget *parent)
    : QDialog (parent), ui (new Ui::InfoDialog) {
  ui->setupUi (this);

  QObject::connect(ui->buttonBox, &QDialogButtonBox::clicked, this, [this](QAbstractButton *button){
    //get the buton first, from QAbstractButton abstract class
    auto stdButton = ui->buttonBox->standardButton(button);

    if (stdButton == QDialogButtonBox::Ok) {
      qDebug() << "You have clicked Ok.";
      this->accept();
    }
   });

  QObject::connect(ui->buttonBox, &QDialogButtonBox::clicked, this, [this](QAbstractButton *button){
    //get the buton first, from QAbstractButton abstract class
    auto stdButton = ui->buttonBox->standardButton(button);

    if (stdButton == QDialogButtonBox::Open) {
      qDebug() << "You have clicked Open.";
      this->accept();
    }
  });

  QObject::connect(ui->buttonBox, &QDialogButtonBox::clicked, this, [this](QAbstractButton *button){
    //get the buton first, from QAbstractButton abstract class
    auto stdButton = ui->buttonBox->standardButton(button);

    if (stdButton == QDialogButtonBox::Cancel) {
      qDebug() << "You have canceled the dialog.";
      this->reject();
    }
  });

}

InfoDialog::~InfoDialog () { delete ui; }

QString InfoDialog::position() const {
  return position_;
}

void InfoDialog::setPosition(const QString &newPosition) {
  position_ = newPosition;
}

QString InfoDialog::favoriteOS() const {
  return favoriteOS_;
}

void InfoDialog::setFavoriteOS(const QString &newFavoriteOS) {
  favoriteOS_ = newFavoriteOS;
}
