#include <QtCore/QMap>
#include <QtGui/QImage>
#include <QtGui/QPixmap>

#include "attachmentmodel.h"
#include "listviewattachment.h"

class ImageCache {
 public:
  struct Item {
    Item() {}
    Item(const QPixmap &p, const QImage &i) : preview(p), image(i) {}
    QPixmap preview;
    QImage image;
    bool isNull() { return preview.isNull(); }
  };
  typedef QMap<QString, Item> Cache;

  Item item(const QString &key) const { return cache_.value(key); }

  void add(const QString &key, const Item &item) { cache_.insert(key, item); }

 private:
  Cache cache_;
};

Q_GLOBAL_STATIC(ImageCache, gImageCache)

AttachmentModel::AttachmentModel(QObject *parent)
    : QAbstractItemModel(parent) {}  // Ctor

AttachmentModel::~AttachmentModel() {}  // Dtor

void AttachmentModel::setModelData(const AttachedItemList &list) {
  beginResetModel();
  list_ = list;
  endResetModel();
}  // setModelData

QModelIndex AttachmentModel::index(int row, int column,
                                   const QModelIndex &parent) const {
  if (parent.isValid()) return QModelIndex();

  return createIndex(row, column);
}  // index

QModelIndex AttachmentModel::parent(const QModelIndex &child) const {
  Q_UNUSED(child);
  return QModelIndex();
}  // parent

int AttachmentModel::rowCount(const QModelIndex &parent) const {
  if (!parent.isValid()) return list_.count();
  return 0;
}  // rowCount

int AttachmentModel::columnCount(const QModelIndex &parent) const {
  if (!parent.isValid()) return ColumnCount;
  return 0;
}  //  columnCount

QVariant AttachmentModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();
  if (role == FileNameRole) {
    return list_.at(index.row()).filename;
  }
  if (role == PreviewRole) {
    const AttachedItem &ai = list_.at(index.row());

    ImageCache::Item item = gImageCache()->item(ai.filename);
    if (item.preview.isNull()) {
      item.image = QImage(ai.filename);
      item.preview = QPixmap::fromImage(
          item.image.scaled(ListViewAttachment::maxPreviewWidth,
                            ListViewAttachment::maxPreviewHeight,
                            Qt::KeepAspectRatio, Qt::SmoothTransformation));

      gImageCache()->add(ai.filename, item);
    }
    return QVariant::fromValue(item.preview);
  }

  //    if (role != Qt::DisplayRole) return QVariant();

  //    const AttachedItem &item = list_.at(index.row());

  //    switch (index.column()) {
  //    case FileNameColumn:
  //        return item.filename;
  //    default:
  //        return QVariant();
  //    }
  return QVariant();
}  // data
