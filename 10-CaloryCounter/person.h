#ifndef PERSON_H
#define PERSON_H

#include <QObject>

class Person : public QObject {
  Q_OBJECT
public:
  explicit Person (QObject *parent = nullptr);
  double weight() const;
  void setWeight(double newWeight);

private:
  double weight_=0.0;
};

#endif // PERSON_H
