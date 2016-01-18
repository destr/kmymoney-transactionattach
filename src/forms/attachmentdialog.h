#pragma once

#include <QtCore/qglobal.h>
#include <QtCore/QAbstractItemModel>

#include <QtGui/QDialog>

#include "attachmentstorage.h"

namespace Ui {
class AttachmentDialog;
}

class AttachmentDialog : public QDialog {
    Q_OBJECT

public:
    explicit AttachmentDialog(QWidget *parent = 0);
    ~AttachmentDialog();

    void setModel(QAbstractItemModel *model);
    void setStorage(AttachmentStorage *storage);

public slots:
    void addAttachment();
    void removeAttachment();

private:
    Ui::AttachmentDialog *ui;

private:
    Q_DISABLE_COPY(AttachmentDialog)
};
