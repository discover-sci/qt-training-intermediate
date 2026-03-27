#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QObject>
#include <QColor>
#include <QLabel>
#include <QGridLayout>
#include <vector>
#include <QWidget>


class ColorPicker : public QWidget {
  Q_OBJECT
public:
  explicit ColorPicker (QWidget *parent = nullptr);

  QColor color() const;
  void setColor(const QColor &newColor);

public:
  Q_SIGNAL void colorChanged(QColor newColor);
private:
  Q_SLOT void handleColorButtonClicked();

private:
  void populateColors();
  void setupUi();


private:
  QColor color_;
  std::vector<QColor> colorList_;
  QGridLayout* gridLayout_{nullptr};
  QLabel* previewLabel{nullptr};

};

#endif // COLORPICKER_H
