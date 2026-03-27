#include "person.h"

Person::Person (QObject *parent) : QObject{ parent } {}

double Person::weight() const
{
  return weight_;
}

void Person::setWeight(double newWeight)
{
  weight_ = newWeight;
}
