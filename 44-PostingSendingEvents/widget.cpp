#include "widget.h"
#include "./ui_widget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <memory>
#include <QMouseEvent>


Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  this->button1 = new Button{this};
  button1->setText("Receive Event");

  QPushButton* button2 = new QPushButton{this};
  button2->setText("Send Event");

  auto *layout = new QVBoxLayout(this);
  layout->addWidget(button1);
  layout->addWidget(button2);
  button1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  button2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


  QObject::connect(button2, &QPushButton::clicked, this, [this](){

    // creates a synthetic mouse‑press event at position (10,10) inside the widget
    // makes no sense for using smart pointer, BUT Gakwaya used it anyway
    auto mouseEvent = std::make_unique<QMouseEvent>(
        QEvent::MouseButtonPress,
        QPointF(10, 10),
        button1->mapToGlobal(QPointF(10, 10)),
        Qt::LeftButton,
        Qt::LeftButton,
        Qt::NoModifier
        );

    // Post event -  Qt takes ownership of the event. See the docs
    // !! asynchronous mode !!
    QApplication::postEvent(button1, mouseEvent.release());


    // Send event - Qt is not going to take ownership here. See the docs
    // mouseEvent.get() gets the raw pointer on a resource in smart pointer
    // !! synchronous mode !!
    if (QApplication::sendEvent(button1, mouseEvent.get())) {
      qDebug() << "Event accepted";
    } else {
      qDebug() << "Event not accepted";
    }
  });

}

Widget::~Widget () { delete ui; }
