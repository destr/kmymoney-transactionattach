#pragma once

#include <QtCore/qglobal.h>
#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QUrl>

struct AttachedItem {
  explicit AttachedItem(const QString& f) : filename(f) {}
  QString filename;
  bool operator==(const AttachedItem& rhs) const {
    return filename == rhs.filename;
  }
};

typedef QList<AttachedItem> AttachedItemList;
uint qHash(const AttachedItem& item);

class AbstractAttachmentStorage : public QObject {
  Q_OBJECT
public:
  AbstractAttachmentStorage() {}
  virtual AttachedItemList load() = 0;
  virtual void addFiles(const QStringList &list) = 0;
  virtual void setPath(const QString &path) = 0;
  virtual void removeFiles(const QStringList &list) = 0;
  virtual void setTransactionId(const QString &transaction) = 0;
  virtual void commit() = 0;
  virtual void rollback() = 0;

private:
  Q_DISABLE_COPY(AbstractAttachmentStorage)
};
