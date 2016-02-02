#pragma once

#include <QtCore/qglobal.h>
#include <QtCore/QScopedPointer>
#include <QtCore/QString>
#include <QtCore/QStringList>

#include "abstractattachmentstorage.h"

class AttachmentModel;

class AttachmentStorageFilesystem : public AbstractAttachmentStorage {
 public:
  AttachmentStorageFilesystem();
  ~AttachmentStorageFilesystem();

  StorageType type() const;

  const QString& transactionId() const;
  void setTransactionId(const QString& id);

  void addFiles(const QStringList& files);
  void setPath(const QString& path);
  void removeFiles(const QStringList& files);
  AttachedItemList load();

  void commit();
  void rollback();

private:

  enum EndType{
      Rollback,
      Commit
  };

  void internalEnd(EndType type);

 private:
  struct Private;
  QScopedPointer<Private> d_;

 private:
  Q_DISABLE_COPY(AttachmentStorageFilesystem)
};
