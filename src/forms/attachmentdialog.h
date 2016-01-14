#pragma once

#include <QtCore/qglobal.h>
#include <QtCore/QAbstractItemModel>

#include <QtGui/QDialog>

namespace Ui {
class AttachmentDialog;
}

class AttachmentDialog : public QDialog {
    Q_OBJECT

public:
    explicit AttachmentDialog(QWidget *parent = 0);
    ~AttachmentDialog();

    void setModel(QAbstractItemModel *model);

private:
    Ui::AttachmentDialog *ui;

private:
    Q_DISABLE_COPY(AttachmentDialog)
};
