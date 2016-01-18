#pragma once

#include <QtGui/QStyledItemDelegate>

class AttachDelegate : public QStyledItemDelegate {
  Q_OBJECT
 public:
  explicit AttachDelegate(QObject* parent = 0);
  ~AttachDelegate();

  // QAbstractItemDelegate interface
 public:
  void paint(QPainter* painter, const QStyleOptionViewItem& option,
             const QModelIndex& index) const;
  QSize sizeHint(const QStyleOptionViewItem& option,
                 const QModelIndex& index) const;

 private:
  Q_DISABLE_COPY(AttachDelegate)
};
