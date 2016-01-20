#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QUrl>
#include <QtGui/QImageReader>

#include "attachmentmodel.h"
#include "attachmentstorage.h"

namespace {
const QString newPrefix = "+";
const QString removePrefix = "-";
}

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

void AttachmentStorage::addFiles(const QStringList &files) {
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

void AttachmentStorage::setPath(const QString &path) {
  d_->dir.setPath(path);
}  // setPath

void AttachmentStorage::removeFiles(const QStringList &files) {
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

AttachedItemList AttachmentStorage::load() {
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

void AttachmentStorage::commit() { internalEnd(Commit); }  // commit

void AttachmentStorage::rollback() { internalEnd(Rollback); }  // rollback

void AttachmentStorage::internalEnd(AttachmentStorage::EndType type) {
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

uint qHash(const AttachedItem &item) { return qHash(item.filename); }
