#include "infodialog.h"
#include "ui_infodialog.h"

InfoDialog::InfoDialog (QWidget *parent)
    : QDialog (parent), ui (new Ui::InfoDialog) {
  ui->setupUi (this);

  QObject::connect(ui->okPushButton, &QPushButton::clicked, this, [this](){

    QString userPosition = ui->positionLineEdit->text();

    // validation evaluation
    if (!userPosition.isEmpty()) {
      this->position_ = userPosition;

      if (ui->winRadioButton->isChecked())
        this->favoriteOS_ = "Windows";

      if (ui->macRadioButton->isChecked())
        this->favoriteOS_ = "Mac OS";

      if (ui->linuxRadioButton->isChecked())
        this->favoriteOS_ = "Linux";

      // accept the dialog
      this->accept();

    } else {
      // reject if filed is not a valid field
      this->reject();

    }


  });

  QObject::connect(ui->cancelPushButton, &QPushButton::clicked, this, [this](){
    // reject the dialog
    this->reject();
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
