#ifndef DATETIMEWIDGET_H
#define DATETIMEWIDGET_H

#include <QWidget>
#include <QDate>
#include <QLabel>
#include <QTimer>

class DateTimeWidget : public QWidget {
  Q_OBJECT
public:
  explicit DateTimeWidget (QWidget *parent = nullptr);

private:
  QTimer timer_;
  QLabel* dateLabel_{nullptr};
  QLabel* timeLabel_{nullptr};
  QString currentDate_;
  QString currentTime_;

private:
  Q_SLOT void updateTime();

};

#endif // DATETIMEWIDGET_H
