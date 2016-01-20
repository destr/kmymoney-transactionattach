#pragma once

#include <QtCore/qglobal.h>
#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QUrl>

typedef QList<QUrl> UrlList;

class AbstractAttachmentStorage : public QObject {
  Q_OBJECT
public:
  AbstractAttachmentStorage() {}
  virtual void addFiles(const QStringList &list) = 0;
  virtual void setPath(const QString &path) = 0;
  virtual void removeFiles(const QStringList &list) = 0;

private:
  Q_DISABLE_COPY(AbstractAttachmentStorage)
};
