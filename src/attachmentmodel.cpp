#include <QtCore/QDebug>
#include <QtCore/QMap>
#include <QtGui/QPixmap>

#include "attachmentmodel.h"
#include "listviewattachment.h"

class ImageCache {
 public:
  struct Item {
    Item() {}
    Item(const QPixmap &p, const QPixmap &i) : preview(p), image(i) {}
    QPixmap preview;
    QPixmap image;
    bool isNull() { return preview.isNull(); }
  };
  typedef QMap<QString, Item> Cache;

  Item item(const QString &key) const { return cache_.value(key); }
  void add(const QString &key, const Item &item) { cache_.insert(key, item); }
  void remove(const QString &key) { cache_.remove(key); }

 private:
  Cache cache_;
};

Q_GLOBAL_STATIC(ImageCache, gImageCache)

AttachmentModel::AttachmentModel(QObject *parent)
    : QAbstractItemModel(parent), storage_(new AttachmentStorage) {}  // Ctor

AttachmentModel::~AttachmentModel() { delete storage_; }  // Dtor

void AttachmentModel::addFiles(const UrlList &files) {
  storage_->addFiles(files);
}  // addFiles

void AttachmentModel::setTransactionId(const QString &transactionId) {
  storage_->setTransactionId(transactionId);
  beginResetModel();
  list_ = storage_->load();
  endResetModel();
}  // setTransactionId

void AttachmentModel::setStoragePath(const QString &path) {
  storage_->setPath(path);
}  // setStoragePath

void AttachmentModel::removeSelected(QModelIndexList indexList) {
  QStringList deletedFiles;
  /// sort by one column
  qSort(indexList);
  for (int i = indexList.count() - 1; i >= 0; --i) {
    const QModelIndex &index = indexList.at(i);
    const int row = index.row();
    const QString filename = list_.at(row).filename;
    deletedFiles.push_back(filename);
    beginRemoveRows(QModelIndex(), row, row);
    list_.removeAt(row);
    endRemoveRows();
    gImageCache()->remove(filename);
  }
}  // removeSelected

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
  const AttachedItem &ai = list_.at(index.row());
  if (role == PreviewRole) {
    ImageCache::Item item = gImageCache()->item(ai.filename);
    if (item.preview.isNull()) {
      QImage image(ai.filename);
      QSize size(ListViewAttachment::previewSize);
      if (image.width() > image.height()) {
        size.transpose();
      }
      item.preview = QPixmap::fromImage(
          image.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
      item.image = QPixmap::fromImage(image);

      gImageCache()->add(ai.filename, item);
    }
    return QVariant::fromValue(item.preview);
  }
  if (role == ImageRole) {
    return QVariant::fromValue(gImageCache()->item(ai.filename).image);
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
