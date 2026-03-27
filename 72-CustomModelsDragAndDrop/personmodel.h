#ifndef PERSONMODEL_H
#define PERSONMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QStringList>
#include <QMimeData>


class PersonModel : public QAbstractListModel {
  Q_OBJECT
public:
  explicit PersonModel (QObject *parent = nullptr);

private:
  QStringList persons;

signals:

  // QAbstractItemModel interface
public:
  int rowCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  bool insertRows(int row, int count, const QModelIndex &parent) override;
  bool removeRows(int row, int count, const QModelIndex &parent) override;
  QStringList mimeTypes() const override;
  QMimeData *mimeData(const QModelIndexList &indexes) const override;
  bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
};

#endif // PERSONMODEL_H
