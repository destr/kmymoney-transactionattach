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
  const qreal pwidth = ListViewAttachment::maxPreviewWidth;
  const qreal pheight = ListViewAttachment::maxPreviewHeight;

  const QPointF top(r.x() + (r.width() - pwidth) / 2,
                    r.y() + (r.height() - pheight) / 2);

  const QRectF p(top, QSize(pwidth, pheight));

  painter->drawRect(p);

  QPixmap preview = index.data(AttachmentModel::PreviewRole).value<QPixmap>();

  painter->drawPixmap(p, preview, preview.rect());

  painter->restore();
}  // paint

QSize AttachDelegate::sizeHint(const QStyleOptionViewItem& option,
                               const QModelIndex& index) const {
  return QSize(ListViewAttachment::maxPreviewWidth,
               ListViewAttachment::maxPreviewHeight + 10);
}  // sizeHint
