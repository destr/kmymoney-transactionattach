#include <QtCore/QDebug>
#include <QtGui/QFileDialog>
#include <QtGui/QLabel>
#include <QtGui/QScrollBar>

#include "aspectratiopixmaplabel.h"
#include "attachmentdialog.h"
#include "attachmentmodel.h"
#include "ui_attachmentdialog.h"

AttachmentDialog::AttachmentDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AttachmentDialog) {
  ui->setupUi(this);

  connect(ui->actionAdd, SIGNAL(triggered()), this, SLOT(addAttachment()));
  connect(ui->actionRemove, SIGNAL(triggered()), this,
          SLOT(removeAttachment()));

  connect(ui->actionFitToScreen, SIGNAL(triggered(bool)), this,
          SLOT(fitToScreen(bool)));
  connect(ui->checkBoxFitToScreen, SIGNAL(clicked(bool)), this,
          SLOT(fitToScreen(bool)));

  connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accepted()));
  connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(rejected()));
  connect(ui->actionFitToScreen, SIGNAL(triggered(bool)),
          ui->checkBoxFitToScreen, SLOT(setChecked(bool)));
  connect(ui->checkBoxFitToScreen, SIGNAL(clicked(bool)),
          ui->actionFitToScreen, SLOT(setChecked(bool)));

  ui->toolButtonAdd->setDefaultAction(ui->actionAdd);
  ui->toolButtonRemove->setDefaultAction(ui->actionRemove);

  ui->listView->addAction(ui->actionAdd);
  ui->listView->addAction(ui->actionRemove);

  label_ = new AspectRatioPixmapLabel(this);
  // label_->setScaledContents(true);
  ui->scrollArea->setBackgroundRole(QPalette::Dark);
  ui->scrollArea->setWidget(label_);
  ui->scrollArea->addAction(ui->actionFitToScreen);

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
  QStringList files =
      QFileDialog::getOpenFileNames(this, tr("Select files"), QString(), "");

  AttachmentModel *model = attachmentModel();
  if (!model) return;

  model->addFiles(files);
}  // addAttachment

void AttachmentDialog::removeAttachment() {
  QModelIndexList indexList;
  QItemSelectionModel *selection = ui->listView->selectionModel();
  if (!selection) return;
  indexList = selection->selectedRows();

  AttachmentModel *model = attachmentModel();
  if (!model) return;
  model->removeSelected(indexList);
}  // removeAttachment

void AttachmentDialog::fitToScreen(bool checked) {
  QSize size;
  if (checked) {
    size = viewportSize();
    label_->resize(size);
  } else {
    label_->resetToOrigPixmap();
  }
}  // fitToScreen

void AttachmentDialog::slot_currentRowChanged(const QModelIndex &current,
                                              const QModelIndex &previous) {
  Q_UNUSED(previous);
  QPixmap pixmap = current.data(AttachmentModel::ImageRole).value<QPixmap>();
  QSize size;
  if (ui->actionFitToScreen->isChecked()) {
    size = viewportSize();
  }
  label_->setPixmap(pixmap, size);
}  // slot_currentRowChanged

void AttachmentDialog::accepted() {
  AttachmentModel *model = attachmentModel();
  if (model) {
    model->commit();
  }
  accept();
}  // accepted

void AttachmentDialog::rejected() {
  AttachmentModel *model = attachmentModel();
  if (model) {
    model->rollback();
  }
  reject();
}  // rejected

AttachmentModel *AttachmentDialog::attachmentModel() {
  return qobject_cast<AttachmentModel *>(ui->listView->model());
}  // attachmentModel

QSize AttachmentDialog::viewportSize() const {
  QScrollArea *area = ui->scrollArea;
  QSize size = area->viewport()->size();
  if (area->horizontalScrollBar()->isVisible()) {
    size.rheight() += area->horizontalScrollBar()->height();
  }
  if (area->verticalScrollBar()->isVisible()) {
    size.rwidth() += area->verticalScrollBar()->width();
  }
  return size;
}  // viewportSize
