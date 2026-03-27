#ifndef PERSON_H
#define PERSON_H

#include <QObject>

class Person : public QObject {
  Q_OBJECT
public:
  explicit Person (QObject *parent = nullptr);
  Person(const QString &names, const QString &favoritecolor, const int &age , QObject * parent = nullptr);

  QString names() const;
  void setNames(const QString &newNames);

  QString favoriteColor() const;
  void setFavoriteColor(const QString &newFavoriteColor);

  int age() const;
  void setAge(int newAge);

private:
  QString names_;
  QString favoriteColor_;
  int age_;


signals:
  void namesChanged(QString names);
  void favoriteColorChanged(QString favoriteColor);
  void ageChanged(int age);
};

#endif // PERSON_H
