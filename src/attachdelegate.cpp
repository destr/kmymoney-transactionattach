#include <QtCore/QDebug>
#include <QtCore/QMap>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtGui/QPixmap>

#include "attachmentmodel.h"
#include "attachdelegate.h"
#include "listviewattachment.h"

AttachDelegate::AttachDelegate(QObject* parent)
    : QStyledItemDelegate(parent) {}  // Ctor

AttachDelegate::~AttachDelegate() {}  // Dtor

void AttachDelegate::paint(QPainter* painter,
                           const QStyleOptionViewItem& option,
                           const QModelIndex& index) const {
  QStyledItemDelegate::paint(painter, option, index);

  painter->save();

  const QRect r = option.rect;

  QPixmap preview = index.data(AttachmentModel::PreviewRole).value<QPixmap>();
  QSize psize = preview.size();

  const QPointF top(r.x() + (r.width() - psize.width()) / 2,
                    r.y() + (r.height() - psize.height()) / 2);

  const QRectF p(top, psize);

  painter->drawRect(p);

  painter->drawPixmap(p, preview, preview.rect());

  painter->restore();
}  // paint

QSize AttachDelegate::sizeHint(const QStyleOptionViewItem& option,
                               const QModelIndex& index) const {
  Q_UNUSED(option)
  QSize size = index.data(AttachmentModel::PreviewRole).value<QPixmap>().size();
  return size + QSize(0, 10);
}  // sizeHint
