#ifndef PERSONMODEL_H
#define PERSONMODEL_H

#include <QObject>
#include "person.h"
#include <QAbstractListModel>

class PersonModel : public QAbstractListModel {
  Q_OBJECT
  enum PersonRoles {
    NamesRole = Qt::UserRole + 1, // enumeration begins from Qt::UserRole on, specifically reserved for user custom roles
    FavoriteColorRole,
    AgeRole
  };

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

  void addPerson(Person* person); // add a specific Person object
  void addPerson(); // add a default Person object
  void addPerson(const QString& names, const int age);  // add a specific Person names and age
  void removePerson(QModelIndex index);

  // take changes from the View and write them back into the model.
  bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;

  // QAbstractItemModel interface
public:
  bool insertRows(int row, int count, const QModelIndex &parent) override;
  bool removeRows(int row, int count, const QModelIndex &parent) override;
  QHash<int, QByteArray> roleNames() const override;
};

#endif // PERSONMODEL_H
