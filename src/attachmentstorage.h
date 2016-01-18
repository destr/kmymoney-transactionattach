#pragma once

#include <QtCore/qglobal.h>
#include <QtCore/QScopedPointer>
#include <QtCore/QString>

#include "abstractattachmentstorage.h"

class AttachmentModel;

class AttachmentStorage : public AbstractAttachmentStorage {
 public:
  explicit AttachmentStorage();
  ~AttachmentStorage();

  const QString& transactionId() const;
  void setTransactionId(const QString& id);

  AttachmentModel* model();
  void addFiles(const UrlList& files);
  void setPath(const QString& path);

 private:
  void load();

 private:
  struct Private;
  QScopedPointer<Private> d_;

 private:
  Q_DISABLE_COPY(AttachmentStorage)
};
