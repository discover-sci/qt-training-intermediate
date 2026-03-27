#include "widget.h"
#include "./ui_widget.h"
#include "QObject"
#include <QMimeData>

Widget::Widget (QWidget *parent) : QWidget (parent), ui (new Ui::Widget) {
  ui->setupUi (this);

  dragDropLabel = new DragDropLabel{this};
  QObject::connect(ui->clearPushButton, &QPushButton::clicked, this, [this](){
    ui->textEdit->clear();

  });


  QObject::connect(dragDropLabel, &DragDropLabel::mimeChanged, this, [this](const QMimeData *mimedata){

    ui->textEdit->clear();
    if (!mimedata) {
      return;
    }

    const QStringList formats = mimedata->formats(); // formats supported by our MIME
    int index = 0;
    for (const QString& format : formats) {
      QString text;
      if (format == QLatin1String("text/plain")) {
        text = mimedata->text().simplified();
      }
      else if (format == QLatin1String("text/html")) {
        text = mimedata->html().simplified();
      }
      else if (format == QLatin1String("text/uri-list")) {
        const QList<QUrl> urlList = mimedata->urls();
        for (const auto& url : urlList) {
          text.append(url.toString() + " -/- ");
        }
      } else {
        const QByteArray data = mimedata->data(format);
        for (const char byte : data) {
          text.append(QString("%1 ").arg(static_cast<unsigned char>(byte)));
        }
      }
      const QString dataString = QString("%1 | Format : %2\n    | Data : %3\n------------")
                                     .arg(index++)
                                     .arg(format)
                                     .arg(text);

      ui->textEdit->append(dataString);

    }

  });

  ui->verticalLayout->insertWidget(0,dragDropLabel);
}

Widget::~Widget() {
  delete ui;
}
