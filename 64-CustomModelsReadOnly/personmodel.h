#ifndef PERSONMODEL_H
#define PERSONMODEL_H

#include <QObject>
#include "person.h"
#include <QAbstractListModel>

class PersonModel : public QAbstractListModel {
  Q_OBJECT
public:
  explicit PersonModel (QObject *parent = nullptr);
  ~PersonModel() override;


private:
  QList<Person*> persons;


  // QAbstractItemModel interface
public:
  int rowCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;

  // QAbstractItemModel interface
public:

  // take changes from the View and write them back into the model.
  bool setData(const QModelIndex &index, const QVariant &value, int role) override;

  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

  Qt::ItemFlags flags(const QModelIndex &index) const override;
};

#endif // PERSONMODEL_H
