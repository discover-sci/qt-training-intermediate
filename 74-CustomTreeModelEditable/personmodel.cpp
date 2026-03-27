#include "personmodel.h"
#include <QIODevice>
#include <QFile>

PersonModel::PersonModel(QObject *parent)
    : QAbstractItemModel{parent} {

  // virtual data for virtual Person, which is actually some sort of a header for all the elements in the tree
  QVector<QVariant> rootData;
  rootData << "Names" << "Proffession"; // header strings
  rootPerson = std::make_unique<Person>(rootData);

  readFile();

}

// return the QModelIndex child of the parent in row and column on the fly
QModelIndex PersonModel::index(int row, int column, const QModelIndex &parent) const {
  if(!hasIndex(row,column,parent))
    return QModelIndex();

         //Go from the QAbstractItemModel model to our domain Person.
  Person* parentPerson = parent.isValid() ? static_cast<Person*> (parent.internalPointer()) : rootPerson.get();

         //Get the child at a given row from a domain Person class
  Person* childPerson = parentPerson->child(row); // child(row) goes into the vector of children in Person domain class

         // if child has been found, create a QModelIndex structure and return it
  if(childPerson){
    return this->createIndex(row, column, childPerson);
  }
  return QModelIndex();

}

QModelIndex PersonModel::parent(const QModelIndex &child) const {
  if(!child.isValid())
    return QModelIndex();

  Person* childPerson = static_cast<Person*>(child.internalPointer());  // get domain child object from index object
  Person* parentPerson = childPerson->parentPerson();                   // get child's domain parent object

  if(parentPerson == rootPerson.get()) // if we are on top - virtual not a proper Person domain object but a headers "Person" object
    return QModelIndex{};

  return this->createIndex(parentPerson->row(), 0, parentPerson);  // create a model object on the parent domain object parentPerson


}

int PersonModel::rowCount(const QModelIndex &parent) const {

  // Items in the first column are parents, other columns represent properties
  if (parent.column() > 0)
    return 0;

         // based on the received QModelIndex param, get the domain object
         // parent.isValid() checks if row and column are valid and if internal pointer is valid
  Person* parentPerson = parent.isValid() ? static_cast<Person*>(parent.internalPointer()):rootPerson.get();
  return parentPerson->childCount();

}

int PersonModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return 2; //Names and Profession, only two columns
}

QVariant PersonModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid())
    return QVariant();

  if (role != Qt::DisplayRole && role != Qt::EditRole)
    return QVariant();

  Person* person = static_cast<Person*> (index.internalPointer());
  return person->data(index.column()); // return the value that is in the column() position in the QVector of properties for the Person
}

bool PersonModel::setData(const QModelIndex &index, const QVariant &value, int role) {
  if (role != Qt::EditRole)
    return false;
  Person* person = static_cast<Person*> (index.internalPointer());
  bool result = person->setData(index.column(), value);

  if (result)
    emit dataChanged(index, index, {role}); // {} means that it is an intializer list and role is the only role in this list

  return result;
}

QVariant PersonModel::headerData(int section, Qt::Orientation orientation, int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
    if (section == 0)
      return tr("Names");
    else if (section == 1)
      return tr("Profession");
  }
  return QVariant();
}


Qt::ItemFlags PersonModel::flags(const QModelIndex &index) const {
  if (!index.isValid())
    return Qt::NoItemFlags;

  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}


void PersonModel::readFile() {
  QString filename = ":/data/familytree.txt";
  QFile inputFile(filename);

  if(!inputFile.open(QIODevice::ReadOnly)) {
    qDebug() << "Could not open the file: " << filename;
    return;
  }else {
    qDebug() << "File opened successfuly for reading!";
  }

  QTextStream in(&inputFile);
  Person* lastParent = rootPerson.get();
  Person* lastPerson = nullptr;
  int lastIndentation{0};

  while(!in.atEnd()){
    QString line = in.readLine();
    int currentIndentation = line.count('\t');

    QVector<QVariant> data = parsePersonData(line.trimmed());

    int indentDiff = currentIndentation - lastIndentation;

    if(indentDiff == 0){
      //Add the child under the current parent
      auto person = std::make_unique<Person>(data,lastParent);
      lastPerson = person.get();
      lastParent->appendChild(std::move(person));
    }else if( indentDiff > 0){
      //Go deeper in the hierarchy
      lastParent = lastPerson;
      auto person = std::make_unique<Person>(data,lastParent);
      lastPerson = person.get();
      lastParent->appendChild(std::move(person));
    }else{
      //Dif in indentation is negative: Navigate back in the tree structure to figure out the right parent.
      for( int i = 0; i < -indentDiff; ++i){
        lastParent = lastParent->parentPerson();
      }

      auto person = std::make_unique<Person>(data,lastParent);
      lastPerson = person.get();
      lastParent->appendChild(std::move(person));

    }
    lastIndentation = currentIndentation;
  }
  inputFile.close();
}

QVector<QVariant> PersonModel::parsePersonData(const QString &line) {
  QStringList parts = line.split('(');
  QVector<QVariant> data;
  data << parts[0].trimmed();
  if(parts.size() > 1){
    QString proffesion = parts[1];
    proffesion.chop(1);
    data << proffesion;
  }else{
    data << QString();
  }
  return data;
}


// insert a new row in the tree under some parent
// On models that support this, inserts count rows into the model before the given row.
bool PersonModel::insertRows(int row, int count, const QModelIndex &parent) {

  Person* parentItem = parent.isValid() ? static_cast<Person*>(parent.internalPointer()) : rootPerson.get();
  bool success = false;
  this->beginInsertRows(parent, row, row + count - 1);

  // insert the domain object into domain container (), begin adding at the row position from the beginning and add count domain objects
  success = parentItem->insertChildren(row, count, 2); // begin adding at row position under parent item, count number of child items with 2 columns each

  this->endInsertRows();

  if (success) {
    saveFile();
  }
  return success;
}

bool PersonModel::removeRows(int row, int count, const QModelIndex &parent) {

  Person* parentItem = parent.isValid() ? static_cast<Person*>(parent.internalPointer()) : rootPerson.get();
  bool success = false;

  this->beginRemoveRows(parent, row, row + count - 1);

  success = parentItem->removeChildren(row, count);

  this->endRemoveRows();

  if (success) {
    saveFile();
  }
  return success;

}


bool PersonModel::saveFile()
{
  QString filename = "data/familytree.txt";
  QFile outputFile(filename);
  if(!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)){
    qDebug() << "Cannot open file for writing:" << filename << " - " << outputFile.errorString();
    return false;
  }

  QTextStream out(&outputFile);

         //Write all children of the root item
  for(int i = 0; i < rootPerson->childCount(); ++i){
    writePersonToStream(out,rootPerson->child(i), 0);
  }

  out.flush();
  outputFile.close();
  return true;
}

void PersonModel::writePersonToStream(QTextStream &out, Person *person, int indent) const
{
  if(!person)
    return;

         //Create indentation with tabs
  QString indentation;
  for(int i = 0; i < indent; ++i){
    indentation += "\t";
  }

         //Format the line: name(proffession)
  QString name = person->data(0).toString();
  QString proffession = person->data(1).toString();
  QString line = indentation + name;

  if(!proffession.isEmpty()){
    line += "(" + proffession + ")";
  }
  out << line << "\n";

         //Write the the children recursively
  for(int i = 0; i < person->childCount(); ++i){
    writePersonToStream(out,person->child(i), indent + 1);
  }
}




















