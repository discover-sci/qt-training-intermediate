#include "logindialog.h"
#include <QLineEdit>
#include <QFormLayout>
#include <QDialogButtonBox>


LoginDialog::LoginDialog () {

  this->setWindowTitle("Database Login");


  domainLoginCheck = new QCheckBox("Use domain login");

  serverCombo = new QComboBox();
  serverCombo->setEditable(true);   // user can type OR pick from list
  serverCombo->addItems({"bpw-denali.ts.telekom.si", "btw-denali.ts.telekom.si"}); // optional


  userEdit = new QLineEdit();
  passwordEdit = new QLineEdit();
  passwordEdit->setEchoMode(QLineEdit::Password);

  // Disable username/password when domain login is checked
  QObject::connect(domainLoginCheck, &QCheckBox::toggled, this, [=](bool checked) {
    userEdit->setEnabled(!checked);
    passwordEdit->setEnabled(!checked);
  });

  QFormLayout *form = new QFormLayout();
  form->addRow("Server:", serverCombo);
  form->addRow("Username:", userEdit);
  form->addRow("Password:", passwordEdit);
  form->addRow("", domainLoginCheck);

  QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

  connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

  QVBoxLayout* layout = new QVBoxLayout();
  layout->addLayout(form);
  layout->addWidget(buttons);

  setLayout(layout);

  this->adjustSize();

  this->setMinimumHeight(height());
  this->setMaximumHeight(height());

  this->setMinimumWidth(350);
  this->setMaximumWidth(600);

}


QString LoginDialog::server() const { return serverCombo->currentText(); }
QString LoginDialog::username() const { return userEdit->text(); }
QString LoginDialog::password() const { return passwordEdit->text(); }
bool LoginDialog::useDomainLogin() const { return domainLoginCheck->isChecked(); }
