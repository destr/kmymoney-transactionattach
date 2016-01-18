#include <QtCore/QDebug>

#include "attachmentdialog.h"
#include "ui_attachmentdialog.h"

AttachmentDialog::AttachmentDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AttachmentDialog) {
  ui->setupUi(this);

  connect(ui->actionAdd, SIGNAL(triggered()), this, SLOT(addAttachment()));
  connect(ui->actionRemove, SIGNAL(triggered()), this, SLOT(removeAttachment()));

  ui->toolButtonAdd->setDefaultAction(ui->actionAdd);
  ui->toolButtonRemove->setDefaultAction(ui->actionRemove);

  ui->listView->addAction(ui->actionAdd);
  ui->listView->addAction(ui->actionRemove);
}  // Ctor

AttachmentDialog::~AttachmentDialog() { delete ui; }  // Dtor

void AttachmentDialog::setModel(QAbstractItemModel *model) {
  ui->listView->setModel(model);
}  // setModel

void AttachmentDialog::setStorage(AttachmentStorage* storage) {
  ui->listView->setStorage(storage);
}  // setStorage

void AttachmentDialog::addAttachment() {
  qDebug() << Q_FUNC_INFO;
}  // addAttachment

void AttachmentDialog::removeAttachment() {
  qDebug() << Q_FUNC_INFO;
}  // removeAttachment
