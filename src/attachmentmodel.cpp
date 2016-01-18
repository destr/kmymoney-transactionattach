#include "attachmentmodel.h"

AttachmentModel::AttachmentModel(QObject *parent) : QAbstractItemModel(parent) {

}  // Ctor

AttachmentModel::~AttachmentModel() {

}  // Dtor

void AttachmentModel::setModelData(const AttachedItemList &list) {
    beginResetModel();
    list_ = list;
    endResetModel();
}  // setModelData

QModelIndex AttachmentModel::index(int row, int column, const QModelIndex &parent) const {
    if (parent.isValid()) return QModelIndex();

    return createIndex(row, column);
}  // index

QModelIndex AttachmentModel::parent(const QModelIndex &child) const {
    Q_UNUSED(child);
    return QModelIndex();
}  // parent

int AttachmentModel::rowCount(const QModelIndex &parent) const {
    if (!parent.isValid()) return list_.count();
    return 0;
}  // rowCount

int AttachmentModel::columnCount(const QModelIndex &parent) const {
    if (!parent.isValid()) return ColumnCount;
    return 0;
}  //  columnCount

QVariant AttachmentModel::data(const QModelIndex &index, int role) const {
//    if (!index.isValid()) return QVariant();
//    if (role != Qt::DisplayRole) return QVariant();

//    const AttachedItem &item = list_.at(index.row());

//    switch (index.column()) {
//    case FileNameColumn:
//        return item.filename;
//    default:
//        return QVariant();
//    }
    return QVariant();
}  // data
