#pragma once

#include <QtCore/qglobal.h>
#include <QtCore/QAbstractItemModel>
#include <QtCore/QList>
#include <QtCore/QScopedPointer>

#include "abstractattachmentstorage.h"
#include "attachmentstoragefactory.h"
#include "attachmentstoragefilesystem.h"

class AttachmentModel : public QAbstractItemModel {
  Q_OBJECT
 public:
  enum Columns { FileNameColumn, ColumnCount };

  enum Roles { FileNameRole = Qt::UserRole + 1, PreviewRole, ImageRole };

  explicit AttachmentModel(QObject *parent = 0);
  AttachmentModel(StorageType type, const QString &path, QObject *parent = 0);
  ~AttachmentModel();

  void addFiles(const QStringList &files);
  void setTransactionId(const QString &transactionId);

  void setStoragePath(const QString &path);
  void setStorageType(StorageType type);

  void removeSelected(QModelIndexList indexList);

  void commit();
  void rollback();

  void reloadConfiguration();
  // QAbstractItemModel interface
 public:
  QModelIndex index(int row, int column, const QModelIndex &parent) const;
  QModelIndex parent(const QModelIndex &child) const;
  int rowCount(const QModelIndex &parent) const;
  int columnCount(const QModelIndex &parent) const;
  QVariant data(const QModelIndex &index, int role) const;

private:
  void createStorage();

 private:
  struct Private;
  QScopedPointer<Private> d_;

  AbstractAttachmentStorage *storage_;
  AttachedItemList list_;
 private:
  Q_DISABLE_COPY(AttachmentModel)
};
