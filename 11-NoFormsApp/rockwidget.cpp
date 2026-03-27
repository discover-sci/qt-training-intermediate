#include "rockwidget.h"
#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
//#include <QMovie>

Rockwidget::Rockwidget (QWidget *parent) : QWidget{ parent } {
  // Here you can set up components on your widget
  QLabel *label = new QLabel{this};
  // label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  label->setText("first line\nsecond line");
  label->setAlignment(Qt::AlignTop | Qt::AlignLeft);
  label->move(50,50);
  // label->show(); // child is visible automatically, when its parent gets visible

  QPalette label1Palette;
  label1Palette.setColor(QPalette::Window, Qt::yellow);
  label1Palette.setColor(QPalette::WindowText, Qt::blue);

  QFont label1Font{"Times", 20, QFont::Bold};

  QLabel *label1 = new QLabel{this};
  label1->setAutoFillBackground(true);
  label1->setText("My custom label");
  label1->setFont(label1Font);
  label1->setPalette(label1Palette);
  label1->move(150,50);
  // label1->show();  // child is visible automatically, when its parent gets visible

  QFont buttonFont{"Times", 20, QFont::Bold};
  QPushButton *button = new QPushButton(this);
  button->setText("Start");
  button->setFont(buttonFont);
  button->move(200, 200);
  QObject::connect(button, &QPushButton::clicked, this, &Rockwidget::buttonClicked);
  // button->show();  // child is visible automatically, when its parent gets visible


  // an example of running the gif as a label
  // QLabel *label = new QLabel(this);   // child of a visible widget
  // QMovie *movie = new QMovie("./bugs-bunny-hold-up-doc.gif");
  // label->setMovie(movie);
  // movie->start();
  // label->show();





}

QSize Rockwidget::sizeHint() const {
  return QSize(700, 700);
}

void Rockwidget::buttonClicked() {
  QMessageBox::information(this, "Info", "Yo have just clicked the buttonBox. Congrats !");

}
