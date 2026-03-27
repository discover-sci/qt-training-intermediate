#ifndef PERSONMODEL_H
#define PERSONMODEL_H

#include <QAbstractItemModel>
#include <QObject>
#include "person.h"

class PersonModel : public QAbstractItemModel {
  Q_OBJECT
public:
  explicit PersonModel(QObject *parent = nullptr);


private:
  std::unique_ptr<Person> rootPerson;

  void readFile();
  QVector<QVariant> parsePersonData(const QString& line);
  bool saveFile();
  void writePersonToStream(QTextStream &out, Person *person, int indent = 0) const;

// QAbstractItemModel interface
public:
  QModelIndex index(int row, int column, const QModelIndex &parent) const override;
  QModelIndex parent(const QModelIndex &child) const override;
  int rowCount(const QModelIndex &parent) const override;
  int columnCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;

  // make the model Eidtable
  bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  bool insertRows(int row, int count, const QModelIndex &parent) override;
  bool removeRows(int row, int count, const QModelIndex &parent) override;
};

#endif // PERSONMODEL_H
