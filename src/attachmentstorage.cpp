#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QUrl>
#include <QtGui/QImageReader>

#include "attachmentmodel.h"
#include "attachmentstorage.h"

struct AttachmentStorage::Private {
  Private() : model(new AttachmentModel) {}
  ~Private() { delete model; }

  QString transactionId;
  AttachmentModel *model;
  QDir dir;
  QString attachPath() {
    return dir.filePath(transactionId);
  }
};

AttachmentStorage::AttachmentStorage() : d_(new Private) {}  // Ctor

AttachmentStorage::~AttachmentStorage() {}  // Dtor

const QString &AttachmentStorage::transactionId() const {
  return d_->transactionId;
}  // transactionId

void AttachmentStorage::setTransactionId(const QString &id) {
  if (d_->transactionId == id) return;
  d_->transactionId = id;
  load();
}  // setTransactionId

AttachmentModel *AttachmentStorage::model() { return d_->model; }  // model

void AttachmentStorage::addFiles(const UrlList &files) {
  QDir dir(d_->attachPath());
  int counter(dir.count());
  Q_FOREACH (QUrl url, files) {
    if (!url.isLocalFile()) continue;

    QImageReader reader(url.toLocalFile());
    if (reader.format().isEmpty()) {
      continue;
    }

    QFile origFile(url.toLocalFile());
    origFile.copy(QString("%1/%2").arg(d_->attachPath()).arg(counter));
    ++counter;
  }
}  // addFiles

void AttachmentStorage::setPath(const QString &path) {
  d_->dir.setPath(path);
  load();
}  // setPath

void AttachmentStorage::load() {
  if (d_->transactionId.isEmpty()) return;

  AttachedItemList list;

  const QString path = d_->dir.filePath(d_->transactionId);
  qDebug() << "Load from: " << path;

#if 0
  for (int i = 0; i < 10; ++i) {
    list.push_back(AttachedItem(QString("filename_%1").arg(i)));
  }
  d_->model->setModelData(list);
#endif
}  // load
