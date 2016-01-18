#include <QtGui/QPainter>

#include "attachdelegate.h"

AttachDelegate::AttachDelegate(QObject* parent)
    : QStyledItemDelegate(parent) {}  // Ctor

AttachDelegate::~AttachDelegate() {}  // Dtor

void AttachDelegate::paint(QPainter* painter,
                           const QStyleOptionViewItem& option,
                           const QModelIndex& index) const {

  QStyledItemDelegate::paint(painter, option, index);

  painter->save();

  const QRect r = option.rect;
  const qreal pwidth = 100;
  const qreal pheight = 100;

  const QPointF top(r.x() + (r.width() - pwidth) / 2,
                    r.y() + (r.height() - pheight) / 2);

  const QRectF p(top, QSize(pwidth, pheight));

  painter->drawRect(p);

  painter->restore();
}  // paint

QSize AttachDelegate::sizeHint(const QStyleOptionViewItem& option,
                               const QModelIndex& index) const {
  return QSize(150, 200);
}  // sizeHint
