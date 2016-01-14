#pragma once

#include <QtCore/qglobal.h>
#include <QtCore/QAbstractItemModel>
#include <QtCore/QList>

struct AttachedItem {
    AttachedItem(const QString &f) : filename(f)
    {}
    QString filename;
};

typedef QList<AttachedItem> AttachedItemList;

class AttachmentModel : public QAbstractItemModel {
    Q_OBJECT
public:
    enum Columns {
        FileNameColumn,
        ColumnCount
    };

    explicit AttachmentModel(QObject *parent = 0);
    ~AttachmentModel();

    void setModelData(const AttachedItemList &list);

    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    AttachedItemList list_;
private:
    Q_DISABLE_COPY(AttachmentModel)
};
