#pragma once

#include <QtCore/qglobal.h>
#include <QtCore/QScopedPointer>
#include <QtCore/QString>
#include <QtCore/QStringList>

#include "abstractattachmentstorage.h"

class AttachmentModel;

struct AttachedItem {
  explicit AttachedItem(const QString& f) : filename(f) {}
  QString filename;
  bool operator==(const AttachedItem& rhs) const {
    return filename == rhs.filename;
  }
};
uint qHash(const AttachedItem& item);

typedef QList<AttachedItem> AttachedItemList;

class AttachmentStorage : public AbstractAttachmentStorage {
 public:
  explicit AttachmentStorage();
  ~AttachmentStorage();

  const QString& transactionId() const;
  void setTransactionId(const QString& id);

  void addFiles(const QStringList& files);
  void setPath(const QString& path);
  void removeFiles(const QStringList& files);
  AttachedItemList load();

 private:
  struct Private;
  QScopedPointer<Private> d_;

 private:
  Q_DISABLE_COPY(AttachmentStorage)
};
