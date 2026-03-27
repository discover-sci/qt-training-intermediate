#include "dbmanager.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QApplication>
#include "locationrow.h"
#include "logindialog.h"


DbManager::DbManager(QObject *parent)
    : QObject (parent) {

}

bool DbManager::connectToDb(QString server, QString user, QString pass, bool domain) {
  // Example using ODBC driver for SQL Server

  // Close old connection if it exists
  if (QSqlDatabase::contains("baznePostajeConnection")) {
    QSqlDatabase old = QSqlDatabase::database("baznePostajeConnection");
    if (old.isOpen())
      old.close();
    QSqlDatabase::removeDatabase("baznePostajeConnection");
  }

    if (domain) {
      this->db = QSqlDatabase::addDatabase("QODBC", "baznePostajeConnection");
      this->db.setDatabaseName("Driver={ODBC Driver 17 for SQL Server};"
                                "Server=" + server + ";"
                                "Database=SQLBazne;"
                                "MARS_Connection=Yes;"
                                "ApplicationIntent=ReadOnly;"
                                "AnsiNPW=Yes;"
                                "Encrypt=No;"             // optional, faster for local networks
                                "Trusted_Connection=yes;" // added for AD login
                                );
    } else {
      this->db = QSqlDatabase::addDatabase("QODBC", "baznePostajeConnection");
      this->db.setDatabaseName("Driver={ODBC Driver 17 for SQL Server};"
                                "Server=" + server + ";"
                                "Database=SQLBazne;"
                                "MARS_Connection=Yes;"
                                "ApplicationIntent=ReadOnly;"
                                "AnsiNPW=Yes;"
                                "Encrypt=No;"                      // optional, faster for local networks
                                );

      this->db.setUserName(user);
      this->db.setPassword(pass);
      this->db.open();
  }

    if (!this->db.open()) {
      qDebug() << "DB open failed:" << this->db.lastError().text();
      return false;
    }

    return true;
}

QVector<LocationRow> DbManager::fetchd48DataFromDb() {
  QVector<LocationRow> result{};
  if (this->db.isOpen() && this->db.isValid()) {
    result.reserve(7000);
    QSqlQuery query{this->db};
    query.setForwardOnly(true);
    QString queryString = "SELECT "
                          "[GKx],"
                          "[GKy],"
                          "[GKn],"
                          "[GKe],"
                          "[Ime],"
                          "[ImeBSC] "
                          "FROM [SQLBazne].[dbo].[Lokacija]";

    if (query.exec(queryString)) {
      while (query.next()) {
        LocationRow location;
        location.x = query.value(0).toInt();
        location.y = query.value(1).toInt();
        location.n = query.value(2).toDouble();
        location.e = query.value(3).toDouble();
        location.ime = query.value(4).toString();
        location.bsc = query.value(5).toString();

               //qDebug() << location.bsc;
        result.append(location);
      }
    } else {
      qDebug() << "Query failed:" << query.lastError().text();
    }
  }
  return result;
}

bool DbManager::connectionValid() const {
  return this->db.isOpen() && this->db.isValid();
}




