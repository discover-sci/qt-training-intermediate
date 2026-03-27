#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow (QWidget *parent = nullptr);

private:
  QAction *quitAction;
private:
  Q_SLOT void buttonClicked();

  // QWidget interface
private:
  QSize sizeHint() const;
};

#endif // MAINWINDOW_H
