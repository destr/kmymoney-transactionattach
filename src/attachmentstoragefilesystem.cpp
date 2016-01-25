#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QUrl>
#include <QtGui/QImageReader>

#include "attachmentmodel.h"
#include "attachmentstoragefilesystem.h"

namespace {
const QString newPrefix = "+";
const QString removePrefix = "-";
}

struct AttachmentStorageFilesystem::Private {
  QString transactionId;
  QDir dir;
  QString attachPath() { return dir.filePath(transactionId); }
};

AttachmentStorageFilesystem::AttachmentStorageFilesystem() : d_(new Private) {}  // Ctor

AttachmentStorageFilesystem::~AttachmentStorageFilesystem() {}  // Dtor

const QString &AttachmentStorageFilesystem::transactionId() const {
  return d_->transactionId;
}  // transactionId

void AttachmentStorageFilesystem::setTransactionId(const QString &id) {
  if (d_->transactionId == id) return;
  d_->transactionId = id;
}  // setTransactionId

void AttachmentStorageFilesystem::addFiles(const QStringList &files) {
  QDir dir(d_->attachPath());
  if (!dir.exists()) {
    dir.mkpath(".");
  }
  int counter(dir.count());
  Q_FOREACH (const QString &filename, files) {
    QImageReader reader(filename);
    if (reader.format().isEmpty()) {
      continue;
    }

    QFile origFile(filename);
    QFileInfo finfo(filename);
    if (!origFile.copy(QString("%1/%2%3_%4.%5")
                           .arg(d_->attachPath())
                           .arg(newPrefix)
                           .arg(counter)
                           .arg(QDateTime::currentMSecsSinceEpoch())
                           .arg(finfo.suffix()))) {
      qDebug() << "Copy file error: " << origFile.errorString();
      continue;
    }
    ++counter;
  }
}  // addFiles

void AttachmentStorageFilesystem::setPath(const QString &path) {
  d_->dir.setPath(path);
}  // setPath

void AttachmentStorageFilesystem::removeFiles(const QStringList &files) {
  QDir dir(d_->attachPath());
  Q_FOREACH (const QString &filepath, files) {
    QFileInfo fi(filepath);
    const QString filename(fi.fileName());
    if (filename.startsWith(newPrefix)) {
        dir.remove(filename);
    } else {
        dir.rename(filename, removePrefix + filename);
    }
  }
}  // removeFiles

AttachedItemList AttachmentStorageFilesystem::load() {
  AttachedItemList list;
  if (d_->transactionId.isEmpty()) return list;

  const QString path = d_->attachPath();
  qDebug() << "Load from: " << path;

  QDir dir(path);
  Q_FOREACH (const QString &filename, dir.entryList(QDir::Files)) {
    list.push_back(AttachedItem(dir.filePath(filename)));
  }

  return list;
}  // load

void AttachmentStorageFilesystem::commit() { internalEnd(Commit); }  // commit

void AttachmentStorageFilesystem::rollback() { internalEnd(Rollback); }  // rollback

void AttachmentStorageFilesystem::internalEnd(AttachmentStorageFilesystem::EndType type) {
  QDir dir(d_->attachPath());
  QStringList filters;
  filters << newPrefix + "*";
  filters << removePrefix + "*";
  Q_FOREACH (const QString &filename, dir.entryList(filters, QDir::Files)) {
    if (filename.startsWith(newPrefix)) {
      switch (type) {
        case Rollback:
          dir.remove(filename);
          break;
        case Commit:
          dir.rename(filename, filename.right(filename.count() - 1));
          break;
      }
    } else if (filename.startsWith(removePrefix)) {
      switch (type) {
        case Rollback:
          dir.rename(filename, filename.right(filename.count() - 1));
          break;
        case Commit:
          dir.remove(filename);
          break;
      }
    }
  }
}  // internalEnd


