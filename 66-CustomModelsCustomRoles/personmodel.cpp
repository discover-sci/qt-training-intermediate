#include "personmodel.h"
#include "person.h"


PersonModel::PersonModel (QObject *parent)
    : QAbstractListModel{ parent } {

  //Populate with initial data

  persons.append(new Person("Jamie Lannister","red",33));
  persons.append(new Person("Marry Lane","cyan",26));
  persons.append(new Person("Steve Moors","yellow",44));
  persons.append(new Person("Victor Trunk","dodgerblue",30));
  persons.append(new Person("Ariel Geeny","blue",33));
  persons.append(new Person("Knut Vikran","lightblue",26));
}

PersonModel::~PersonModel() {
  qDeleteAll(persons);

}


int PersonModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return persons.size();
}

QVariant PersonModel::data(const QModelIndex &index, int role) const {
  if (index.row() < 0 || index.row() >= persons.count())
    return QVariant();

  Person* person = persons[index.row()];

  if(role == Qt::DisplayRole || role == Qt::ToolTipRole || role == Qt::EditRole || role == NamesRole){
    return person->names();
  }

  if(role == FavoriteColorRole) {
    return person->favoriteColor();
  }

  if(role == AgeRole) {
    return person->age();
  }

  return QVariant();
}

void PersonModel::addPerson(Person *person) {
  this->insertRows(persons.size(),1,QModelIndex()); // ModelIndex() is root parent
  QModelIndex idx = this->index(persons.size()-1, 0); // index returns the QModelIndex in certain row and column
  this->setData(idx, person->names(), NamesRole);
  this->setData(idx, person->favoriteColor(), FavoriteColorRole);
  this->setData(idx, person->age(), AgeRole);

}


void PersonModel::addPerson() {
  Person* person = new Person("Generic John", "yellowgreen", 45);
  this->addPerson(person); //forward the call to addPerson(const QString &names, const int age)
}

void PersonModel::addPerson(const QString &names, const int age) {
  Person* person = new Person(names, "yellowgreen", age);
  this->addPerson(person);

}

void PersonModel::removePerson(QModelIndex index) {
  if (index.isValid())
    this->removeRows(index.row(), 1, QModelIndex());
}



bool PersonModel::setData(const QModelIndex &index, const QVariant &value, int role) {
  if (!index.isValid())
    return false;

  Person* person = persons[index.row()];
  bool somethingChanged = false;

  switch (role) {
    case Qt::EditRole:
    case NamesRole: {
      if (person->names() != value.toString()) {
        person->setNames(value.toString());
        somethingChanged = true;
      }
    }
    break;
    case AgeRole: {
      if(person->age() != value.toInt()){
        person->setAge(value.toInt());
        somethingChanged = true;
      }
    }
    break;

    case FavoriteColorRole: {
      if(person->favoriteColor() != value.toString()){
        person->setFavoriteColor(value.toString());
        somethingChanged = true;
      }
    }
  }

  if (somethingChanged) {
    emit dataChanged(index, index);
    return true;
  }

  return false;
}


/*
If orientation == Qt::Horizontal,
section is the column number.

If orientation == Qt::Vertical,
section is the row number.

We have one column, so:
Horizontal header → section is always 0
Vertical header → section is the row number
*/
QVariant PersonModel::headerData(int section, Qt::Orientation orientation, int role) const {
  if(role != Qt::DisplayRole) {
    return QVariant();
  }

  if(orientation == Qt::Horizontal){
    return QString("Person names");
  }

         //Vertical headers
  return QString("Person %1").arg(section);
}

Qt::ItemFlags PersonModel::flags(const QModelIndex &index) const {
  if (!index.isValid())
    return QAbstractListModel::flags(index);  // call default flags (which is Qt::NoItemFlags)

  return QAbstractListModel::flags(index) | Qt::ItemIsEditable; // otherwise all what is by default and enable "editability"

}


// only add a new Row, no content (Person object) in the model yet
bool PersonModel::insertRows(int row, int count, const QModelIndex &parent) {

  beginInsertRows(QModelIndex(), row, row + count - 1);
  for(int i = 0; i < count; ++i){
    persons.insert(row, new Person()); // Insert a placeholder instead of a true Person.
  }
  endInsertRows();

  return true;
}

// just remove a row
bool PersonModel::removeRows(int row, int count, const QModelIndex &parent) {

  beginRemoveRows(QModelIndex(), row, row + count - 1);
  persons.removeAt(row);
  endRemoveRows();

  return true;
}



QHash<int, QByteArray> PersonModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[NamesRole] = "names";
  roles[FavoriteColorRole] = "favoritecolor";
  roles[AgeRole] = "age";
  return roles;

}












