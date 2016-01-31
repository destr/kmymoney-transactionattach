#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QDebug>

#include "attachmentstoragesqlite.h"

namespace {
const QString connectionName("kmymoney-transactionattach");
const QString databaseName("attachments");
}

struct AttachmentStorageSqlite::Private {
    QString dbfile;
    QSqlDatabase db;
};

AttachmentStorageSqlite::AttachmentStorageSqlite() : d_(new Private) {}  // Ctor

AttachmentStorageSqlite::~AttachmentStorageSqlite() {}  // Dtor

AttachedItemList AttachmentStorageSqlite::load() {
  return AttachedItemList();
}  // load

void AttachmentStorageSqlite::addFiles(const QStringList& list) {}  // addFiles

void AttachmentStorageSqlite::setPath(const QString& path) {
    qDebug() << Q_FUNC_INFO << path;
    d_->dbfile = path;

    d_->db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    if (!d_->db.isValid()) {
        qDebug() << "Database is invalid";
        return;
    }

    d_->db.setDatabaseName(databaseName);
    if (!d_->db.open()) {
        qDebug() << d_->db.lastError();
    }
    qDebug() << "db opened";
}

void AttachmentStorageSqlite::removeFiles(const QStringList& list) {}

void AttachmentStorageSqlite::setTransactionId(const QString& transaction) {}

void AttachmentStorageSqlite::commit() {}

void AttachmentStorageSqlite::rollback() {}
