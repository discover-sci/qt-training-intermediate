#include "dragdroplabel.h"
#include <QDragEnterEvent>
#include <QMimeData>

DragDropLabel::DragDropLabel (QWidget *parent)
    : QLabel{ parent } {

  // setting up Label properties
  this->setMinimumSize(100, 100);
  this->setAlignment(Qt::AlignCenter);
  this->setAcceptDrops(true);
  this->setText(tr("DROP SPACE"));
  this->setAutoFillBackground(true);

}

void DragDropLabel::clear() {
  qDebug() << "Clear called.";
  setText(tr("DROP SPACE"));
  setBackgroundRole(QPalette::Dark);
  emit mimeChanged();
}

// What do we do when the drag operation enters our widget ?
// The event parameter contains information about the drag operation.
void DragDropLabel::dragEnterEvent(QDragEnterEvent *event) {
  setText(tr("DROP YOUR DATA HERE"));
  setBackgroundRole(QPalette::Highlight);
  event->acceptProposedAction();  // you say: OK, you can drop this MIME on my widget. Default value is non accepting.
  emit mimeChanged(event->mimeData()); // fire the signal, that something entered into your widget.

}

// What doe we do when the drag operation moves within our widget?
void DragDropLabel::dragMoveEvent(QDragMoveEvent *event) {
  qDebug() << "Moving a drop inside your widget.";
  event->acceptProposedAction();
}

void DragDropLabel::dragLeaveEvent(QDragLeaveEvent *event) {
  this->clear(); // slot to clear the label of all text content
}

void DragDropLabel::dropEvent(QDropEvent *event) {

  const QMimeData* const mimeData = event->mimeData();

  // What to do with our label, when you drop a MIME on it ?
  // depending on what type of properties the MIME has
  if (mimeData->hasText()) {
    this->setText(mimeData->text());    // called on Label
    this->setTextFormat(Qt::PlainText); // called on label
  } else if (mimeData->hasImage()) {
    setPixmap(qvariant_cast<QPixmap>(mimeData->imageData())); // set label as pixmap
  } else if (mimeData->hasHtml()) {
    this->setText(mimeData->html());    // called on label
    this->setTextFormat(Qt::RichText);  // clled on label
  }else if (mimeData->hasUrls()) {
    const QList<QUrl> urlList = mimeData->urls();
    QString text;
    for (const auto& url : urlList) {
      text += url.path() + "-----";
    }
    this->setText(text);
  } else {
    this->setText(tr("Data cannot be displayed"));
  }


}











