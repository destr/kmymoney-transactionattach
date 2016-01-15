#pragma once

#include <QtCore/qglobal.h>
#include <QtCore/QString>

class AttachmentModel;

class AttachmentStorage {
 public:
  explicit AttachmentStorage();
  ~AttachmentStorage();

  const QString& transactionId() const;
  void setTransactionId(const QString& id);

  AttachmentModel* model();

 private:
  void load();

 private:
  QString transactionId_;
  AttachmentModel* model_;

 private:
  Q_DISABLE_COPY(AttachmentStorage)
};
