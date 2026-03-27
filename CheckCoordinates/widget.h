#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "dbmanager.h"
#include "progressdialog.h"



QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
  Q_OBJECT

public:
  explicit Widget (QWidget *parent = nullptr);
  ~Widget () override;

private:
  Q_SLOT void onConnect();
  Q_SLOT void onRead();
  Q_SLOT void onRest();
  Q_SLOT void onCompare();
  Q_SLOT void dataReadyRead();
  Q_SLOT void dataReadFinished();


private:
  Ui::Widget *ui;
  DbManager* dbManager;
  QNetworkAccessManager* netManager;
  QNetworkReply* netReply;
  QVector<LocationRow> rowsDB;
  int currentRestRow = 0;
  ProgressDialog *progressDialog = nullptr;

  QIcon iconNotOk;
  QIcon iconOk;

  QString currentRcc;


  void sendNextRestRequest();


  // QWidget interface
protected:
  void showEvent(QShowEvent *event) override;
  bool isValidGK(int x, int y);
};
#endif // WIDGET_H
