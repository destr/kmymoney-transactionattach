#pragma once

#include <QtCore/qglobal.h>

#include "abstractattachmentstorage.h"

class AttachmentStorageSqlite : public AbstractAttachmentStorage {
public:
  AttachmentStorageSqlite();
  ~AttachmentStorageSqlite();

  // AbstractAttachmentStorage interface
public:
  AttachedItemList load();
  void addFiles(const QStringList& list);
  void setPath(const QString& path);
  void removeFiles(const QStringList& list);
  void setTransactionId(const QString& transaction);
  void commit();
  void rollback();

private:
  Q_DISABLE_COPY(AttachmentStorageSqlite)
};
