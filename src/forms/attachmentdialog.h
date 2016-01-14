#pragma once

#include <QtGui/QDialog>

namespace Ui {
class AttachmentDialog;
}

class AttachmentDialog : public QDialog {
    Q_OBJECT

public:
    explicit AttachmentDialog(QWidget *parent = 0);
    ~AttachmentDialog();

private:
    Ui::AttachmentDialog *ui;
};
