#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget {
  Q_OBJECT

public:
  Widget (QWidget *parent = nullptr);
  ~Widget ();

private:
  Ui::Widget *ui;
  QNetworkAccessManager *netManager_;
  QNetworkReply *netReply_;
  QByteArray dataBuffer_;

  Q_SLOT void dataReadyRead();
  Q_SLOT void dataReadFinished();
};
#endif // WIDGET_H
