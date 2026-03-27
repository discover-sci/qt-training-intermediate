#include "widget.h"
#include "./ui_widget.h"
#include <QFontDialog>
#include <QMessageBox>

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  QObject::connect(ui->pushButton, &QPushButton::clicked, this, [this](){
    bool ok;
    QFont font = QFontDialog::getFont(
                                        &ok,
                                        // QFont("Helvetica [Cronyx]", 10),  //initially selected font for the label
                                        ui->fontLabel->font(),               //give current label's font as the initial font
                                        this,
                                        QString{"Choose the font for the label..."});
    if (ok) {
      ui->fontLabel->setFont(font);
    } else {
      QMessageBox::information(this,"Message","User did not choose font");
    }
  });
}

Widget::~Widget () { delete ui; }
