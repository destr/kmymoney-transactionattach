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

  void resetToOrigPixmap();
 public slots:
  void setPixmap(const QPixmap &pixmap, const QSize &size = QSize());

  // QWidget interface
 protected:
  void resizeEvent(QResizeEvent *event);

 private:
  void internalSetPixmap(const QSize &size);

 private:
  QPixmap pixmap_;

 private:
  Q_DISABLE_COPY(AspectRatioPixmapLabel)
};
