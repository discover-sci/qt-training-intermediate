#include "container.h"
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QMimeData>
#include <QDrag>
#include "pixmapmime.h"

Container::Container (QWidget *parent)
    : QWidget{ parent } {

  this->setMinimumSize(150, 150);
  this->setAcceptDrops(true);

  auto *qtIcon = new QLabel(this);
  qtIcon->setPixmap(QPixmap{":/images/qt.png"});
  qtIcon->move(20, 20);
  qtIcon->show();
  qtIcon->setAttribute(Qt::WA_DeleteOnClose); // a close() on this label is going to be called

  auto *cppIcon = new QLabel(this);
  cppIcon->setPixmap(QPixmap{":/images/cpp.png"});
  cppIcon->move(150, 20);
  cppIcon->show();
  cppIcon->setAttribute(Qt::WA_DeleteOnClose);  // a close() on this label is going to be called

  auto *terminalIcon = new QLabel(this);
  terminalIcon->setPixmap(QPixmap{":/images/terminal.png"});
  terminalIcon->move(20, 150);
  terminalIcon->show();
  terminalIcon->setAttribute(Qt::WA_DeleteOnClose);  // a close() on this label is going to be called
}


void Container::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton)
    this->startPos = event->pos();
  QWidget::mousePressEvent(event);
}

void Container::mouseMoveEvent(QMouseEvent *event) {

  if (event->buttons() & Qt::LeftButton) { // check which mous buttons were pressed by using bitwise AND on buttons() bits

    int distance = (event->pos() - this->startPos).manhattanLength();

    if (distance >= QApplication::startDragDistance()) { // Is distance greater than default one
                                                         // This property holds the minimum distance required for a drag and drop operation to start.

      // Start Drag Operation
      QLabel* child = static_cast<QLabel *>(this->childAt(event->pos()));
      if(!child)
        return;


      QPixmap mPixmap = child->pixmap();

      // we package pixmap and metadata on it into a custom PixmapMime
      auto *mimeData = new PixmapMime(mPixmap, QPoint(event->pos() - child->pos()),"Item icon");


      QDrag* drag = new QDrag(this);
      drag->setMimeData(mimeData);
      drag->setPixmap(mPixmap);
      drag->setHotSpot(event->pos() - child->pos());  // Make sure the cursor is at the right position relative to the dragged item
                                                      // i.e. The argument is a point in the child label’s coordinate system so
                                                      // the cursor appears to grab the same pixel the user clicked.

      // Blur the original label
      QPixmap tempPix = mPixmap;
      QPainter painter(&tempPix);
      painter.fillRect(tempPix.rect(),QColor(127, 127, 127, 127)); // Semi-transparent effect
      child->setPixmap(tempPix);

      // Call to drag->exec() is blocking, thread stops, until returned from exec() method
      // Qt::CopyAction is the default - the second param in the exec() method call
      if(drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction) {
        // Move data
        qDebug()<< "Moving data";
        child->close(); // We assume the data has made it to the new widget, so we close(delete) the original widget
      } else {
        // The only other option - the default one is a Copy action
        child->setPixmap(mPixmap);  // restore the previous image on the label, since it was blurred
        qDebug() << "Copying data";
      }

    }

  }
}

void Container::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.drawRoundedRect(0,5,width()-10, height()-10,1,1); // recatangle drawn will be bound to Container
                                                            // so resizing works
  QWidget::paintEvent(event);
}

void Container::dragEnterEvent(QDragEnterEvent *event) {

  // qobject_cast returns nullptr if it does not succeed
  if (const auto *mimeData = qobject_cast<const PixmapMime*>(event->mimeData())) {
    if (event->source() == this) {
      event->setDropAction(Qt::MoveAction);
      event->accept();
    } else {
      event->acceptProposedAction();
    }
  } else {
    event->ignore();
  }
}

void Container::dragMoveEvent(QDragMoveEvent *event) {

}

void Container::dropEvent(QDropEvent *event) {
  const auto *mimeData = qobject_cast<const PixmapMime*>(event->mimeData());
  if (!mimeData) {
    event->ignore();
    return;
  }

         //Extract the data
  QPixmap mPixmap = mimeData->pix();
  QPoint offset = mimeData->offset();

         //Create a label that we will drop
  QLabel * newLabel = new QLabel(this);
  newLabel->setPixmap(mPixmap);
  newLabel->move(event->position().toPoint() - offset);
  newLabel->show();
  newLabel->setAttribute(Qt::WA_DeleteOnClose);

  if (event->source() == this) {
    event->setDropAction(Qt::MoveAction);
    event->accept();
                      //event->ignore();
  } else {
    event->acceptProposedAction();
  }
}
