#include "attachmentstoragesqlite.h"

AttachmentStorageSqlite::AttachmentStorageSqlite() {}  // Ctor

AttachmentStorageSqlite::~AttachmentStorageSqlite() {}  // Dtor

AttachedItemList AttachmentStorageSqlite::load() {
  return AttachedItemList();
}  // load

void AttachmentStorageSqlite::addFiles(const QStringList& list) {}  // addFiles

void AttachmentStorageSqlite::setPath(const QString& path) {}

void AttachmentStorageSqlite::removeFiles(const QStringList& list) {}

void AttachmentStorageSqlite::setTransactionId(const QString& transaction) {}

void AttachmentStorageSqlite::commit() {}

void AttachmentStorageSqlite::rollback() {}
