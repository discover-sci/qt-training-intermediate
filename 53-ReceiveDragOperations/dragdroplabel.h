#ifndef DRAGDROPLABEL_H
#define DRAGDROPLABEL_H

class QMimeData;

#include <QWidget>
#include <QLabel>

class DragDropLabel : public QLabel {
  Q_OBJECT
public:
  explicit DragDropLabel (QWidget *parent = nullptr);
  void clear();


public:
  Q_SIGNAL void mimeChanged(const QMimeData *mimeData = nullptr);

  // QWidget interface
protected:
  void dragEnterEvent(QDragEnterEvent *event) override;
  void dragMoveEvent(QDragMoveEvent *event) override;
  void dragLeaveEvent(QDragLeaveEvent *event) override;
  void dropEvent(QDropEvent *event) override;
};

#endif // DRAGDROPLABEL_H
