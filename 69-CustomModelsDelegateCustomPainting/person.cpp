#include "person.h"
#include <QDebug>

Person::Person (QObject *parent) : QObject{ parent } {}

Person::Person(const QString &names, const QString &favoritecolor, const int &age, QObject *parent)
    : QObject(parent),
      names_(names),
      favoriteColor_(favoritecolor),
      age_(age) {

}

QString Person::names() const {
  return this->names_;
}

void Person::setNames(const QString &newNames) {
  if (this->names_ == newNames)
    return;
  this->names_ = newNames;
  emit namesChanged(this->names_);
}

QString Person::favoriteColor() const {
  return this->favoriteColor_;
}

void Person::setFavoriteColor(const QString &newFavoriteColor) {
  qDebug() << "Favorite Color called";
  if (this->favoriteColor_ == newFavoriteColor)
    return;

  this->favoriteColor_ = newFavoriteColor;
  emit favoriteColorChanged(this->favoriteColor_);
}

int Person::age() const {
  return this->age_;
}

void Person::setAge(int newAge) {
  if (this->age_ == newAge)
    return;

  this->age_ = newAge;
  emit ageChanged(this->age_);

}
