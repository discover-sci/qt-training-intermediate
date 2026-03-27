#include "widget.h"
#include "./ui_widget.h"
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>



Widget::Widget (QWidget *parent) :
                                   QWidget (parent),
                                   ui (new Ui::Widget),
                                   netManager_(new QNetworkAccessManager(this)),
                                   netReply_(nullptr) {

  ui->setupUi (this);

  QObject::connect(ui->fetchPushButton, &QPushButton::clicked, this, [this](){

    // Initialize our API data
    const QUrl API_ENDPOINT("https://jsonplaceholder.typicode.com/posts");
    QNetworkRequest request;
    request.setUrl(API_ENDPOINT);
    this->netReply_ = this->netManager_->get(request);

    QObject::connect(this->netReply_, &QIODevice::readyRead, this, &Widget::dataReadyRead);
    QObject::connect(this->netReply_, &QNetworkReply::finished, this, &Widget::dataReadFinished);
  });

}


void Widget::dataReadyRead() {
  this->dataBuffer_.append(this->netReply_->readAll());
};

void Widget::dataReadFinished() {

  if (this->netReply_->error()) {
    qDebug() << "Error : " << this->netReply_->errorString();
  } else {
    qDebug() << "Data fetch finished : " << QString(this->dataBuffer_);

           // Turn the data into a json document
    QJsonDocument doc = QJsonDocument::fromJson(this->dataBuffer_);

    /*
    //What if you get an object from the server
    QJsonDocument objectDoc = QJsonDocument::fromJson(dataBuffer_);
    QJsonObject obObject = objectDoc.toVariant().toJsonObject();
    */

           // Turn document into json array
    QJsonArray array = doc.array();

           // take json objects from josn array
    for (int i = 0; i < array.size(); i++) {
      QJsonObject object = array.at(i).toObject();
      QVariantMap map = object.toVariantMap();  //QVariantMap == QMap<String, QVariant>
      QString title = map["title"].toString();
      ui->listWidget->addItem("["+ QString::number(i+1) + "] " + title);

    }
  }
}


  Widget::~Widget () { delete ui; }
