#include "widget.h"
#include "./ui_widget.h"
#include <QFileDialog>

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  QObject::connect(ui->dirOpenPushButton, &QPushButton::clicked, this, [this](){
    QString dir = QFileDialog::getExistingDirectory(this,
                                                     tr("Open Directory"),
                                                     QString{},
                                                     // flags
                                                     QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    if (!dir.isEmpty())
      qDebug() << dir;
    else
      qDebug() << "Nothing has been chosen.";

  });

  QObject::connect(ui->fileOpenPushButton, &QPushButton::clicked, this, [this](){
    QString fileName = QFileDialog::getOpenFileName(this,
                                                     tr("Open File"),
                                                     QString{},
                                                     tr("Images (*.png *.*")
                                                     );
    if (!fileName.isEmpty())
      qDebug() << fileName;
    else
      qDebug() << "No file has been chosen.";

  });

  QObject::connect(ui->openMultiplePushButton, &QPushButton::clicked, this, [this](){
    QStringList fileNames = QFileDialog::getOpenFileNames(this,
                                                     tr("Open more Files"),
                                                     QString{},
                                                      tr("Images (*.png *.*);;Text Files (*.txt);;XML files (*.xml)")
                                                     );
    if (!fileNames.isEmpty())
      for (auto fileName : fileNames)
        qDebug() << fileName;
    else
      qDebug() << "No files has been chosen.";

  });












}

Widget::~Widget () { delete ui; }
