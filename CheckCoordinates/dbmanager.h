#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QWidget>
#include "locationrow.h"



class DbManager : public QObject {
  Q_OBJECT
public:
  DbManager (QObject *parent);

public:
  bool connectToDb(QString server, QString user, QString pass, bool domain);
  QVector<LocationRow> fetchd48DataFromDb();

  bool connectionValid() const;

private:
  QSqlDatabase db;
};

#endif // DBMANAGER_H
