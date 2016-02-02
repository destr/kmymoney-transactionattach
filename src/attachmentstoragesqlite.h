#pragma once

#include <QtCore/qglobal.h>
#include <QtCore/QScopedPointer>

#include "abstractattachmentstorage.h"

class AttachmentStorageSqlite : public AbstractAttachmentStorage {
public:
  AttachmentStorageSqlite();
  ~AttachmentStorageSqlite();

  // AbstractAttachmentStorage interface
public:
  StorageType type() const;
  AttachedItemList load();
  void addFiles(const QStringList& list);
  void setPath(const QString& path);
  void removeFiles(const QStringList& list);
  void exportFiles(const QString &dst, const QStringList &list);
  void setTransactionId(const QString& transaction);
  void commit();
  void rollback();

private:
  struct Private;
  QScopedPointer<Private> d_;

private:
  Q_DISABLE_COPY(AttachmentStorageSqlite)
};
