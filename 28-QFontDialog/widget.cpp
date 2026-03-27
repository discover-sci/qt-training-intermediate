#include "widget.h"
#include "./ui_widget.h"
#include <QColorDialog>
#include <QFontDialog>

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  QObject::connect(ui->colorPushButton, &QPushButton::clicked, this, [this](){

    // the palette is an object that includes all the properties for the widgets
    QPalette palette = ui->label->palette();

    // get the current color for the widget and save it into a var color - so this is the old color used
    QColor color = palette.color(QPalette::WindowText);

    // chose a new color
    QColor chosenColor = QColorDialog::getColor(color,this,"Choose text color");

    if(chosenColor.isValid()) {
      palette.setColor(QPalette::WindowText, chosenColor); //set the new color for text
      ui->label->setPalette(palette);
      qDebug() << "User choose a valid color";
    } else {
      qDebug() << "User choose a invalid color";
    }
  });

  QObject::connect(ui->backgroundPushButton, &QPushButton::clicked, this, [this](){
    QPalette palette = ui->label->palette();
    QColor color = palette.color(QPalette::Window);
    QColor chosenColor = QColorDialog::getColor(color,this,"Choose color");

    if(chosenColor.isValid()) {
      palette.setColor(QPalette::Window, chosenColor);
      ui->label->setPalette(palette);

      /* This command instructs Qt to fill the widget’s background with the brush from its palette (the QPalette::Window role)
       * before painting the widget’s contents.
       */
      ui->label->setAutoFillBackground(true);

      qDebug() << "User choose a valid color";
    } else {
      qDebug() << "User choose a invalid color";
    }
  });

  QObject::connect(ui->fontPushButton, &QPushButton::clicked, this, [this](){
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("Helvetica [Cronyx]", 10), this);
    if (ok) {
      ui->label->setFont(font);
    } else {
      // pass
    }
  });

}

Widget::~Widget () { delete ui; }
