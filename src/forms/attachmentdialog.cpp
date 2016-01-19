#include <QtCore/QDebug>
#include <QtGui/QLabel>

#include "attachmentmodel.h"
#include "attachmentdialog.h"
#include "ui_attachmentdialog.h"

AttachmentDialog::AttachmentDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AttachmentDialog) {
  ui->setupUi(this);

  connect(ui->actionAdd, SIGNAL(triggered()), this, SLOT(addAttachment()));
  connect(ui->actionRemove, SIGNAL(triggered()), this,
          SLOT(removeAttachment()));

  ui->toolButtonAdd->setDefaultAction(ui->actionAdd);
  ui->toolButtonRemove->setDefaultAction(ui->actionRemove);

  ui->listView->addAction(ui->actionAdd);
  ui->listView->addAction(ui->actionRemove);

  label_ = new QLabel(this);
  ui->scrollArea->setBackgroundRole(QPalette::Dark);
  ui->scrollArea->setWidget(label_);
}  // Ctor

AttachmentDialog::~AttachmentDialog() { delete ui; }  // Dtor

void AttachmentDialog::setModel(QAbstractItemModel *model) {
  QItemSelectionModel *selectionModel = ui->listView->selectionModel();
  if (selectionModel) {
    disconnect(selectionModel,
               SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this,
               SLOT(slot_currentRowChanged(QModelIndex, QModelIndex)));
  }
  ui->listView->setModel(model);

  selectionModel = ui->listView->selectionModel();
  connect(selectionModel, SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
          this, SLOT(slot_currentRowChanged(QModelIndex, QModelIndex)));
}  // setModel

void AttachmentDialog::addAttachment() {
  qDebug() << Q_FUNC_INFO;
}  // addAttachment

void AttachmentDialog::removeAttachment() {
  QModelIndexList indexList;
  QItemSelectionModel *selection = ui->listView->selectionModel();
  if (!selection) return;
  indexList = selection->selectedRows();

  AttachmentModel *model =
      qobject_cast<AttachmentModel *>(ui->listView->model());
  if (!model) return;
  model->removeSelected(indexList);
}  // removeAttachment

void AttachmentDialog::slot_currentRowChanged(const QModelIndex &current,
                                              const QModelIndex &previous) {
  Q_UNUSED(previous);
  label_->setPixmap(current.data(AttachmentModel::ImageRole).value<QPixmap>());
}  // removeAttachment
