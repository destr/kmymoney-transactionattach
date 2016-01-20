#include <QtGui/QResizeEvent>
#include <QtCore/QDebug>

#include "aspectratiopixmaplabel.h"

AspectRatioPixmapLabel::AspectRatioPixmapLabel(QWidget* parent)
    : QLabel(parent) {
  // setMinimumSize(1, 1);
}  // Ctor

QSize AspectRatioPixmapLabel::sizeHint() const {
  const int w = width();
  return QSize(w, heightForWidth(w));
}  // sizeHint

int AspectRatioPixmapLabel::heightForWidth(int width) const {
  if (pixmap_.isNull()) return 0;
  return (pixmap_.height() * width) / pixmap_.width();
}  // heightForWidth

void AspectRatioPixmapLabel::resetToOrigPixmap() {
  internalSetPixmap(QSize());
}  // resetToOrigPixmap

void AspectRatioPixmapLabel::setPixmap(const QPixmap& pixmap,
                                       const QSize& size) {
  pixmap_ = pixmap;

  internalSetPixmap(size);
}  // setPixmap

void AspectRatioPixmapLabel::resizeEvent(QResizeEvent* event) {
  if (pixmap_.isNull()) return;
  internalSetPixmap(event->size());
}  // resizeEvent

void AspectRatioPixmapLabel::internalSetPixmap(const QSize& size) {
  if (!size.isValid()) {
    QLabel::setPixmap(pixmap_);
    return;
  }
  QLabel::setPixmap(
      pixmap_.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
