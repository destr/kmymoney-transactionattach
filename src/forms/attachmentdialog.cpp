#include "attachmentdialog.h"
#include "ui_attachmentdialog.h"

AttachmentDialog::AttachmentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AttachmentDialog) {
    ui->setupUi(this);
}  // Ctor

AttachmentDialog::~AttachmentDialog() {
    delete ui;
}  // Dtor
