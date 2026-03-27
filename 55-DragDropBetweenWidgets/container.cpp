#include "container.h"
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QMimeData>
#include <QDrag>

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

      // We have a label below the event position, now get the picture representation of the label
      QPixmap mPixmap = child->pixmap();

      QByteArray ba;  // an object in Qt, to package and manipulate the binary data

      QDataStream dataStream(&ba, QIODevice::WriteOnly);  // convenient function to put data into a byte array, so wrap ba into a stream

      dataStream << mPixmap << QPoint(event->pos() - child->pos());

      QMimeData* mimeData = new QMimeData;
      mimeData->setData("application/x-qtcustomitem", ba);

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
  if (event->mimeData()->hasFormat("application/x-qtcustomitem")) {
    if (event->source() == this) { // moving inside the same source widget that we move/copy from
      event->setDropAction(Qt::MoveAction);
      event->accept();
      //event->ignore();
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
  if (event->mimeData()->hasFormat("application/x-qtcustomitem")) {

    //Extract the data
    QByteArray ba = event->mimeData()->data("application/x-qtcustomitem");
    QDataStream dataStream(&ba,QIODevice::ReadOnly);

    QPixmap mPixmap;
    QPoint offset;

    dataStream >> mPixmap >> offset;

    //Create a label that we will be dropped into this widget
    QLabel * newLabel = new QLabel{this};
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

  }else {
    event->ignore();
  }
}
