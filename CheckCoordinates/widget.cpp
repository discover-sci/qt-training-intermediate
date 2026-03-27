#include "widget.h"
#include "./ui_widget.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include "dbmanager.h"
#include <QXmlStreamReader>
#include <proj.h>
#include "logindialog.h"
#include <QResource>
#include <QFile>


Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  iconNotOk = QIcon(":/icons/nok.png");
  iconOk    = QIcon(":/icons/ok.png");



  QObject::connect(ui->connectButton, &QPushButton::clicked, this, &Widget::onConnect);
  QObject::connect(ui->readButton,    &QPushButton::clicked, this, &Widget::onRead);
  QObject::connect(ui->restButton,    &QPushButton::clicked, this, &Widget::onRest);
  //QObject::connect(ui->compareButton, &QPushButton::clicked, this, &Widget::onCompare);



  this->dbManager = new DbManager{this};

  ui->tableWidget->setColumnCount(9);
  QStringList labels;
  labels << "D48/GK-X" << "D48/GK-Y" << "D96/TM-E" << "D96/TM-N" << "Name" << "BSC" << "REST D96/TM-E" << "REST D96/TM-N" << "Comparison";
  ui->tableWidget->setHorizontalHeaderLabels(labels);
  // ui->tableWidget->horizontalHeader()->setStyleSheet(
  //     "QHeaderView::section {"
  //     "background-color: #9ecbff;"
  //     "color: black;"
  //     "}"
  //     );

  ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  ui->tableWidget->setAlternatingRowColors(true);

  netManager = new QNetworkAccessManager(this);
}


void Widget::showEvent(QShowEvent *event) {
  QWidget::showEvent(event);

         // Switch to interactive resizing AFTER the widget is visible
  ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
}


// helper function
bool Widget::isValidGK(int x, int y)
{
  // GK coordinates for Slovenia roughly fall into these ranges:
  // X: 4,000,000 – 6,000,000
  // Y: 4,500,000 – 5,500,000

  if (x < 4000000 || x > 6000000 || x == 0) return false;
  if (y < 4500000 || y > 5500000 || y == 0) return false;

  return true;
}



void Widget::onConnect() {
  // LoginDialog dlg;

         // if (dlg.exec() == QDialog::Accepted) {
         //   QString server = dlg.server();
         //   QString user   = dlg.username();
         //   QString pass   = dlg.password();
         //   bool domain    = dlg.useDomainLogin();
         //   this->dbManager->connectToDb(server, user, pass, domain);
         //   if (!this->dbManager->connectionValid())
         //     QMessageBox::critical(this, "Error", "Connection failed.");
         //   else
         //     QMessageBox::information(this, "Success", "Connection OK.");
         // } else {

  // }
  LoginDialog dlg;

  if (dlg.exec() != QDialog::Accepted)
    return;

  QString server = dlg.server();
  QString user   = dlg.username();
  QString pass   = dlg.password();
  bool domain    = dlg.useDomainLogin();

  bool ok = this->dbManager->connectToDb(server, user, pass, domain);

  if (!ok)
    QMessageBox::critical(this, "Error", "Connection failed.");
  else
    QMessageBox::information(this, "Success", "Connection OK.");

}

void Widget::onRead() {

  if (this->dbManager->connectionValid()) {
    ui->tableWidget->setRowCount(0);
    this->rowsDB = dbManager->fetchd48DataFromDb();
    if (this->rowsDB.size() > 0) {
      for (int i = 0; i < this->rowsDB.size(); ++i) {
        const LocationRow& location = this->rowsDB[i];
        //qDebug() << location.ime;
        int nextRow = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(nextRow);

        QTableWidgetItem* x = new QTableWidgetItem(QString::number(location.x));
        QTableWidgetItem* y = new QTableWidgetItem(QString::number(location.y));
        QTableWidgetItem* n = new QTableWidgetItem(QString::number(location.n, 'f', 2));
        QTableWidgetItem* e = new QTableWidgetItem(QString::number(location.e, 'f', 2));
        QTableWidgetItem* ime = new QTableWidgetItem(location.ime);
        QTableWidgetItem* bsc = new QTableWidgetItem(location.bsc);

        ui->tableWidget->setItem(nextRow, 0, x);
        ui->tableWidget->setItem(nextRow, 1, y);
        ui->tableWidget->setItem(nextRow, 2, e);
        ui->tableWidget->setItem(nextRow, 3, n);
        ui->tableWidget->setItem(nextRow, 4, ime);
        ui->tableWidget->setItem(nextRow, 5, bsc);

      }

    }
  } else {
    QMessageBox::critical(this, "Cannot continue ...", "No connection to DB. Setup the connection first.");

  }

}


void Widget::onRest() {

  if (rowsDB.isEmpty())
    return;

  currentRestRow = 0;     // start from first row

         // Create modal progress dialog
  progressDialog = new ProgressDialog(this);
  progressDialog->setMaximum(this->rowsDB.size());
  progressDialog->setProgress(0);
  progressDialog->setLabel("Starting REST calls...");
  progressDialog->show();   // modal dialog pops up



  sendNextRestRequest();  // begin sequential processing
}


// void Widget::onRest() {

//   if (this->rowsDB.size() > 0) {
//     for (int i = 0; i < this->rowsDB.size(); ++i) {
//       //const LocationRow& location = this->rowsDB[i];

//       int rawX = rowsDB[i].x;
//       int rawY = rowsDB[i].y;

//       // int rawX = 5387636;
//       // int rawY = 5123605;


//       if (!isValidGK(rawX, rawY)) {
//         ui->tableWidget->setItem(i, 8, new QTableWidgetItem("Invalid GK"));
//         continue;
//       }

//       double x = rawX - 5000000;
//       double y = rawY - 5000000;

//       if (x < -1000000 || x > 1000000 || y < -500000  || y > 500000) {
//         ui->tableWidget->setItem(i, 8, new QTableWidgetItem("Bad transform"));
//         continue;
//       }

//       QUrl url(QString("http://bpw-agsdata.ts.telekom.si:8081/TMGKService/d96/?Y=%1&X=%2&responseType=xml").arg(x).arg(y));

//       QNetworkRequest request(url);
//       // request.setRawHeader("Accept", "application/xml");
//       request.setRawHeader("User-Agent",
//                             "Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
//                             "AppleWebKit/537.36 (KHTML, like Gecko) "
//                             "Chrome/123.0 Safari/537.36");

//       QNetworkReply* reply = netManager->get(request);

//              // store the row index inside the reply
//       reply->setProperty("row", i);
//       reply->setProperty("buffer", QByteArray());

//       QObject::connect(reply, &QNetworkReply::readyRead, this, &Widget::dataReadyRead);
//       QObject::connect(reply, &QNetworkReply::finished, this, &Widget::dataReadFinished);

//     }

//   }

//          // QString xString = "5455286"; //454914.98
//          // QString yString = "5097909"; //98395.56

//          // int xInt = xString.toInt();
//          // int yInt = yString.toInt();

//          // xInt-=5000000;
//          // yInt-=5000000;

//          // const QUrl API_ENDPOINT(QString("http://bpw-agsdata.ts.telekom.si:8081/TMGKService/d96/?Y=%1&X=%2&responseType=xml").arg(xInt).arg(yInt));
//          // // QNetworkRequest request;
//          // request.setUrl(API_ENDPOINT);
//          // // request.setHeader(QNetworkRequest::ContentTypeHeader, "application/xml");
//          // request.setRawHeader("Accept", "application/xml");
//          // this->netReply = this->netManager->get(request);

//          // QObject::connect(this->netReply, &QIODevice::readyRead, this, &Widget::dataReadyRead);
//          // QObject::connect(this->netReply, &QNetworkReply::finished, this, &Widget::dataReadFinished);
//          // Initialize our API data
// }





void Widget::sendNextRestRequest()
{

  if (progressDialog) {
    progressDialog->setProgress(currentRestRow);
    progressDialog->setLabel(
        QString("Processing BSC: %1 (%2 / %3)")
            .arg(rowsDB[currentRestRow].bsc)
            .arg(currentRestRow + 1)
            .arg(rowsDB.size())
        );
  }

  if (currentRestRow >= rowsDB.size()) {
    if (progressDialog) {
      progressDialog->setLabel("Finished.");
      progressDialog->setProgress(rowsDB.size());
      progressDialog->accept();   // closes modal dialog
      progressDialog = nullptr;
    }
    return;
  }

         // if (currentRestRow >= rowsDB.size())
         //   return; // all done

  int rawX = rowsDB[currentRestRow].x;
  int rawY = rowsDB[currentRestRow].y;

  if (!isValidGK(rawX, rawY)) {

    QTableWidgetItem *item = new QTableWidgetItem();
    item->setIcon(QIcon(":/icons/nok.png"));
    item->setText("NOT A VALID GK");
    //item->setToolTip("Invalid GK");   // optional hover text

    ui->tableWidget->setItem(currentRestRow, 8, item);

    currentRestRow++;
    sendNextRestRequest();
    return;
  }

  double x = rawX - 5000000;   // REST X
  double y = rawY - 5000000;   // REST Y

  QString urlString = QString(
                          "http://bpw-agsdata.ts.telekom.si:8081/TMGKService/d96/?Y=%1&X=%2&responseType=xml"
                          ).arg((int)x).arg((int)y);

  QUrl url(urlString);
  QNetworkRequest request(url);

  request.setRawHeader("User-Agent",
                        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
                        "AppleWebKit/537.36 (KHTML, like Gecko) "
                        "Chrome/123.0 Safari/537.36");

  QNetworkReply* reply = netManager->get(request);

  reply->setProperty("row", currentRestRow);
  reply->setProperty("buffer", QByteArray());

  QObject::connect(reply, &QNetworkReply::readyRead,this, &Widget::dataReadyRead);

         // QObject::connect(reply, &QNetworkReply::finished, this, [this, reply]() {
         //            this->dataReadFinished();   // parse XML
         //            reply->deleteLater();
         //            currentRestRow++;           // move to next row
         //            sendNextRestRequest();      // continue queue
         //          });

  connect(reply, &QNetworkReply::finished, this, [this, reply]() {

    this->dataReadFinished();

    reply->deleteLater();
    currentRestRow++;

    if (currentRestRow >= rowsDB.size()) {
      if (progressDialog) {
        progressDialog->setLabel("Finished.");
        progressDialog->setProgress(rowsDB.size());
        progressDialog->accept();
        progressDialog = nullptr;
      }
      return;
    }

    sendNextRestRequest();
  });




}



void Widget::dataReadFinished()
{
  QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
  if (!reply) return;

  if (reply->error()) {
    int row = reply->property("row").toInt();
    ui->tableWidget->setItem(row, 8,
                              new QTableWidgetItem("Bad Request"));
    return;
  }

  int row = reply->property("row").toInt();
  QByteArray buffer = reply->property("buffer").toByteArray();
  QString xml = QString::fromUtf8(buffer);

  QXmlStreamReader reader(xml);

  double eValue = 0.0;
  double nValue = 0.0;
  bool isError = false;

  while (!reader.atEnd() && !reader.hasError()) {
    reader.readNext();

    if (reader.isStartElement()) {
      if (reader.name() == "isError")
        isError = (reader.readElementText() == "true");

      if (reader.name() == "e")
        eValue = reader.readElementText().toDouble();

      if (reader.name() == "n")
        nValue = reader.readElementText().toDouble();
    }
  }

  if (reader.hasError() || isError) {
    ui->tableWidget->setItem(row, 8,
                              new QTableWidgetItem("Bad Request"));
    return;
  }




  ui->tableWidget->setItem(row, 6, new QTableWidgetItem(QString::number(eValue, 'f', 2)));
  ui->tableWidget->setItem(row, 7, new QTableWidgetItem(QString::number(nValue, 'f', 2)));

  QTableWidgetItem* item = new QTableWidgetItem();
  item->setIcon(this->iconOk);   // your icon path
  item->setText("OK");                      // optional
  ui->tableWidget->setItem(currentRestRow, 8, item);

  if ((ui->tableWidget->item(row, 2)->text() != QString::number(eValue, 'f', 2))) {
    auto item2 = ui->tableWidget->item(row, 2);
    item2->setBackground(QColor(0xfc6f6f));
    auto item6 = ui->tableWidget->item(row, 6);

    item6->setBackground(QColor(0xfc6f6f));
    QTableWidgetItem* item = new QTableWidgetItem();
    item->setIcon(this->iconNotOk);   // your icon path
    item->setText("NOT OK");                      // optional
    //item->setBackground(QColor("#fc6f6f"));
    ui->tableWidget->setItem(currentRestRow, 8, item);
  }

  if (ui->tableWidget->item(row, 3)->text() != QString::number(nValue, 'f', 2)) {
    auto item3 = ui->tableWidget->item(row, 3);
    item3->setBackground(QColor(0xfc6f6f));
    auto item7 = ui->tableWidget->item(row, 7);
    item7->setBackground(QColor(0xfc6f6f));

    QTableWidgetItem* item = new QTableWidgetItem();
    item->setIcon(this->iconNotOk);   // your icon path
    item->setText("NOT OK");                      // optional
    //item->setBackground(QColor("#fc6f6f"));
    ui->tableWidget->setItem(currentRestRow, 8, item);

  }




}




void Widget::dataReadyRead() {

  //which reply did receive the data - sender() returns a reply, that called this slot
  QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
  if (!reply) return;

         //get the buffer from reply object
  QByteArray buffer = reply->property("buffer").toByteArray();
  //fill the buffer wit new data
  buffer.append(reply->readAll());
  //set new data to the property
  reply->setProperty("buffer", buffer);
}

/*Processing of XML data in finished block of data*/
// void Widget::dataReadFinished() {

//   QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
//   if (!reply) return;

//   if (reply->error()) {
//     qDebug() << "Error:" << reply->errorString();
//     reply->deleteLater();
//     return;
//   }

//   int row = reply->property("row").toInt();
//   QByteArray buffer = reply->property("buffer").toByteArray();
//   QString xml = QString::fromUtf8(buffer);

//   QXmlStreamReader reader(xml);

//   double eValue = 0.0;
//   double nValue = 0.0;
//   bool isError = false;

//   while (!reader.atEnd() && !reader.hasError()) {
//     reader.readNext();

//     if (reader.isStartElement()) {
//       if (reader.name() == "isError")
//         isError = (reader.readElementText() == "true");

//       if (reader.name() == "e")
//         eValue = reader.readElementText().toDouble();

//       if (reader.name() == "n")
//         nValue = reader.readElementText().toDouble();
//     }
//   }

//   if (reader.hasError()) {
//     qDebug() << "XML parse error:" << reader.errorString();
//     reply->deleteLater();
//     return;
//   }

//   if (isError) {
//     qDebug() << "Service returned error.";
//     reply->deleteLater();
//     return;
//   }

//   ui->tableWidget->setItem(row, 6, new QTableWidgetItem(QString::number(nValue, 'f', 2)));
//   ui->tableWidget->setItem(row, 7, new QTableWidgetItem(QString::number(eValue, 'f', 2)));

//   // if (ui->tableWidget->item(currentRestRow, 2)->text() == QString::number(nValue)) {
//   //   QTableWidgetItem* item = new QTableWidgetItem();
//   //   item->setIcon(QIcon(":/icons/ok.png"));   // your icon path
//   //   item->setText("OK");                      // optional
//   //   ui->tableWidget->setItem(currentRestRow, 6, item);
//   // }





//   reply->deleteLater();
// }




void Widget::onCompare()   {

}

Widget::~Widget () {
  delete ui;
}