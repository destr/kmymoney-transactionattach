#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QUrl>
#include <QtGui/QImageReader>

#include "attachmentmodel.h"
#include "attachmentstorage.h"

struct AttachmentStorage::Private {
  QString transactionId;
  QDir dir;
  QString attachPath() { return dir.filePath(transactionId); }
};

AttachmentStorage::AttachmentStorage() : d_(new Private) {}  // Ctor

AttachmentStorage::~AttachmentStorage() {}  // Dtor

const QString &AttachmentStorage::transactionId() const {
  return d_->transactionId;
}  // transactionId

void AttachmentStorage::setTransactionId(const QString &id) {
  if (d_->transactionId == id) return;
  d_->transactionId = id;
}  // setTransactionId

void AttachmentStorage::addFiles(const UrlList &files) {
  QDir dir(d_->attachPath());
  if (!dir.exists()) {
    dir.mkpath(".");
  }
  int counter(dir.count());
  Q_FOREACH (QUrl url, files) {
    if (!url.isLocalFile()) continue;

    const QString filename(url.toLocalFile());
    QImageReader reader(filename);
    if (reader.format().isEmpty()) {
      continue;
    }

    QFile origFile(filename);
    QFileInfo finfo(filename);
    if (!origFile.copy(QString("%1/%2.%3")
                           .arg(d_->attachPath())
                           .arg(counter)
                           .arg(finfo.suffix()))) {
      qDebug() << "Copy file error: " << origFile.errorString();
      continue;
    }
    ++counter;
  }
}  // addFiles

void AttachmentStorage::setPath(const QString &path) {
  d_->dir.setPath(path);
}  // setPath

void AttachmentStorage::removeFiles(const QStringList &files) {
  Q_FOREACH (const QString file, files) { QFile::remove(file); }
}  // removeFiles

AttachedItemList AttachmentStorage::load() {
  AttachedItemList list;
  if (d_->transactionId.isEmpty()) return list;

  const QString path = d_->attachPath();
  qDebug() << "Load from: " << path;

  QDir dir(path);
  Q_FOREACH (const QString &filename, dir.entryList(QDir::Files)) {
    list.push_back(AttachedItem(dir.filePath(filename)));
  }

#if 0
  for (int i = 0; i < 10; ++i) {
    list.push_back(AttachedItem(QString("filename_%1").arg(i)));
  }
#endif
  return list;
}  // load
