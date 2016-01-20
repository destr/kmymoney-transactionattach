#pragma once

#include <QtCore/qglobal.h>
#include <QtGui/QLabel>
#include <QtGui/QPixmap>

class AspectRatioPixmapLabel : public QLabel {
  Q_OBJECT
 public:
  explicit AspectRatioPixmapLabel(QWidget *parent = 0);

  // QWidget interface
 public:
  virtual QSize sizeHint() const;
  virtual int heightForWidth(int width) const;

public slots:
  void setPixmap(const QPixmap &pixmap);

  // QWidget interface
 protected:
  void resizeEvent(QResizeEvent *event);

 private:
  QPixmap pixmap_;

 private:
  Q_DISABLE_COPY(AspectRatioPixmapLabel)
};
