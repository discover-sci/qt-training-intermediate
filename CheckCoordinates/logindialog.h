#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QObject>
#include <QComboBox>
#include <QCheckBox>


class LoginDialog : public QDialog {
  Q_OBJECT
public:
  explicit LoginDialog();

  QString server() const;
  QString username() const;
  QString password() const;
  bool useDomainLogin() const;

private:
  QComboBox *serverCombo;
  QLineEdit *userEdit;
  QLineEdit *passwordEdit;
  QCheckBox *domainLoginCheck;
};

#endif // LOGINDIALOG_H

