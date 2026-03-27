#include "datetimewidget.h"
#include <QVBoxLayout>

DateTimeWidget::DateTimeWidget (QWidget *parent)
    : QWidget{ parent },
      timer_{this},
      dateLabel_{new QLabel(this)},
      timeLabel_{new QLabel(this)},
      currentDate_{QDate::currentDate().toString(Qt::TextDate)},
      currentTime_{QTime::currentTime().toString()} {

  auto layout = new QVBoxLayout{this};
  const QFont displayFont{"Consolas", 20, QFont::Bold};
  const QSizePolicy sizePolicy{QSizePolicy::Expanding, QSizePolicy::Fixed};

  // Setup date label
  dateLabel_->setText(currentDate_);
  dateLabel_->setFont(displayFont);
  dateLabel_->setAlignment(Qt::AlignCenter);

  // Setup time label
  timeLabel_->setText(currentTime_);
  timeLabel_->setFont(displayFont);
  timeLabel_->setAlignment(Qt::AlignCenter);
  timeLabel_->setSizePolicy(sizePolicy);
  timeLabel_->setStyleSheet(R"(
        background-color: #00eff9;
        color: #fffff1
    )");

  // Layout setup
  layout->addWidget(dateLabel_);
  layout->addWidget(timeLabel_);
  setLayout(layout);
  setSizePolicy(sizePolicy);

  // Timer setup
  timer_.setInterval(1000);
  connect(&timer_, &QTimer::timeout, this, &DateTimeWidget::updateTime);
  timer_.start();

}

void DateTimeWidget::updateTime() {
  const QString newTime = QTime::currentTime().toString();
  timeLabel_->setText(newTime);
  currentTime_ = newTime;


  const QString newDate = QDate::currentDate().toString(Qt::TextDate);
  if (currentDate_ != newDate) {
    dateLabel_->setText(newDate);
    currentDate_ = newDate;
  }

}
