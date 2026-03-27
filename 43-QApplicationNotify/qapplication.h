#ifndef QAPPLICATION_H
#define QAPPLICATION_H

#include <QObject>
#include <QApplication>

class QApplication : public QApplication {
  Q_OBJECT
public:
  explicit QApplication (QObject *parent = nullptr);

signals:
};

#endif // QAPPLICATION_H
