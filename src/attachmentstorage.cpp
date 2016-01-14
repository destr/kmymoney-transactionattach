#include "attachmentstorage.h"
#include "attachmentmodel.h"

AttachmentStorage::AttachmentStorage() :
    model_(new AttachmentModel) {

}  // Ctor

AttachmentStorage::~AttachmentStorage() {
    delete model_;
}  // Dtor

const QString &AttachmentStorage::transactionId() const {
    return transactionId_;
}  // transactionId

void AttachmentStorage::setTransactionId(const QString &id) {
    if (transactionId_ == id) return;
    transactionId_ = id;
    load();
}  // setTransactionId

AttachmentModel *AttachmentStorage::model() {
    return model_;
}  // model

void AttachmentStorage::load() {
    AttachedItemList list;
    for (int i = 0; i < 10; ++i) {
        list.push_back(AttachedItem(QString("filename_%1").arg(i)));

    }
    model_->setModelData(list);
}  // load
