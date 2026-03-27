#include "personmodel.h"
#include "person.h"


//#define ADD_REMOVE_MANUAL
#define ADD_REMOVE_REGULAR

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

  if(role == Qt::DisplayRole || role == Qt::ToolTipRole || role == Qt::EditRole){
    return person->names();
  }

  return QVariant();
}

#if defined(ADD_REMOVE_MANUAL)
/*Qt does  not recommend this approach: use insertRows, removeRows*/
void PersonModel::addPerson(Person *person) {
  const int row = this->persons.size(); // where to put a new person in our QList
  this->beginInsertRows(QModelIndex(), row, row);  // QModelIndex() means root item in our model, add from row to row - in one place effectively
  this->persons.append(person);
  endInsertRows();
}
/*Qt recommends this approach*/
#elif defined(ADD_REMOVE_REGULAR)
void PersonModel::addPerson(Person *person) {
  const int index = this->persons.size(); // where to put a new person in our QList
  if (this->insertRows(index, 1, QModelIndex()))
    this->persons[index] = person; // wit this, the object Person in inserted into the rows of our model
}
#endif



void PersonModel::addPerson() {
  Person* person = new Person("Generic John", "yellowgreen", 45, this);
  this->addPerson(person); //forward the call
}

void PersonModel::addPerson(const QString &names, const int age) {
  Person* person = new Person(names, "yellowgreen", age, this);
  this->addPerson(person);

}

/*Qt does  not recommend this approach: use insertRows, removeRows*/
#if defined(ADD_REMOVE_MANUAL)
void PersonModel::removePerson(QModelIndex index) {
  this->beginRemoveRows(QModelIndex(), index.row(), index.row());  // QModelIndex()means root item in our model
  this->persons.removeAt(index.row());
  endRemoveRows();
}
/*Qt recommends this approach*/
#elif defined(ADD_REMOVE_REGULAR)
void PersonModel::removePerson(QModelIndex index) {
  if (index.isValid())
    this->removeRows(index.row(), 1, QModelIndex());
}
#endif



bool PersonModel::setData(const QModelIndex &index, const QVariant &value, int role) {
  if (!index.isValid())
    return false;

  Person* person = persons[index.row()];

  switch (role) {
  case Qt::EditRole:
    if (person->names() != value.toString()) {
      person->setNames(value.toString());
      emit dataChanged(index, index);
      return true;
    }
    break;
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
  if (parent.isValid())
    return false;

  beginInsertRows(QModelIndex(), row, row + count - 1);
  for(int i = 0; i < count; ++i){
    persons.insert(row, nullptr); // Insert a placeholder instead of a true Person.
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


















