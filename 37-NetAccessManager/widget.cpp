#include "widget.h"
#include "./ui_widget.h"
#include <QNetworkReply>

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  this->netManager =  new QNetworkAccessManager{this};
  this->netReply = nullptr;
  //this->dataBuffer = new QByteArray();

  //Define net request
  QNetworkRequest request;
  //request.setUrl(QUrl("https://www.qt.io"));
  request.setUrl(QUrl("https://www.github.com"));

  netReply = netManager->get(request);

  QObject::connect(netReply, &QIODevice::readyRead, this, [this](){
    // signla came that data is ready to be read
    qDebug() << "Data available.";
    this->dataBuffer.append(netReply->readAll());

  });


  QObject::connect(netReply, &QNetworkReply::finished, this, [this](){
    if (this->netReply->error()) {
      qDebug() << "Error: " << QString(this->dataBuffer);
    } else {
      ui->textEdit->setPlainText(QString(this->dataBuffer));
    }


  });

}

Widget::~Widget () {
  //delete this->dataBuffer;
  delete ui;

}
