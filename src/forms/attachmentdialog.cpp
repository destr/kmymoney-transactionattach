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

  connect(ui->actionRotate90Clockwise, SIGNAL(triggered()), this,
          SLOT(rotate90Clockwise()));
  connect(ui->actionRotate90Anticlockwise, SIGNAL(triggered()), this,
          SLOT(rotate90Anticlockwise()));

  connect(ui->actionExport, SIGNAL(triggered()), this,
          SLOT(exportAttachment()));

  connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accepted()));
  connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(rejected()));

  ui->toolButtonAdd->setDefaultAction(ui->actionAdd);
  ui->toolButtonRemove->setDefaultAction(ui->actionRemove);
  ui->toolButtonExport->setDefaultAction(ui->actionExport);
  ui->toolButtonFitToScreen->setDefaultAction(ui->actionFitToScreen);
  ui->toolButtonRotate90Clockwise->setDefaultAction(
      ui->actionRotate90Clockwise);
  ui->toolButtonRotate90Anticlockwise->setDefaultAction(
      ui->actionRotate90Anticlockwise);

  ui->listView->addAction(ui->actionAdd);
  ui->listView->addAction(ui->actionRemove);
  ui->listView->addAction(ui->actionExport);

  label_ = new AspectRatioPixmapLabel(this);
  ui->scrollArea->setBackgroundRole(QPalette::Dark);
  ui->scrollArea->setWidget(label_);

  ui->scrollArea->addAction(ui->actionFitToScreen);
  ui->scrollArea->addAction(ui->actionRotate90Clockwise);
  ui->scrollArea->addAction(ui->actionRotate90Anticlockwise);

  enableActions(false);
}  // Ctor

AttachmentDialog::~AttachmentDialog() { delete ui; }  // Dtor

void AttachmentDialog::setModel(QAbstractItemModel *model) {
  QItemSelectionModel *selectionModel = ui->listView->selectionModel();
  if (selectionModel) {
    disconnect(selectionModel,
               SIGNAL(currentRowChanged(QModelIndex, QModelIndex)), this,
               SLOT(slot_currentRowChanged(QModelIndex, QModelIndex)));
  }
  QAbstractItemModel *oldModel = ui->listView->model();
  if (oldModel) {
    disconnect(oldModel, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this,
               SLOT(slot_dataChanged(QModelIndex, QModelIndex)));
  }
  ui->listView->setModel(model);

  selectionModel = ui->listView->selectionModel();
  connect(selectionModel, SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
          this, SLOT(slot_currentRowChanged(QModelIndex, QModelIndex)));
  connect(model, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this,
          SLOT(slot_dataChanged(QModelIndex, QModelIndex)));
}  // setModel

void AttachmentDialog::setTransactionInfo(const QString &info) {
  ui->labelTransactionInfo->setText(info);
}  // setTransactionInfo

void AttachmentDialog::addAttachment() {
  QStringList files =
      QFileDialog::getOpenFileNames(this, tr("Select files"), QString(), "");

  AttachmentModel *model = attachmentModel();
  if (!model) return;

  model->addFiles(files);
}  // addAttachment

void AttachmentDialog::removeAttachment() {
  QModelIndexList indexList = selectedIndexes();

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

void AttachmentDialog::exportAttachment() {
  QString path =
      QFileDialog::getExistingDirectory(this, tr("Select export directory"));

  if (path.isEmpty()) return;

  QModelIndexList indexList = selectedIndexes();
  AttachmentModel *model = attachmentModel();
  if (!model) return;
  model->exportSelected(path, indexList);
}  // exportAttachment

void AttachmentDialog::rotate90Clockwise() {
  internalRotate(Clockwise);
}  // rotate90Clockwise

void AttachmentDialog::rotate90Anticlockwise() {
  internalRotate(Anticlockwise);
}  // rotate90Anticlockwise

void AttachmentDialog::slot_currentRowChanged(const QModelIndex &current,
                                              const QModelIndex &previous) {
  Q_UNUSED(previous);
  enableActions(current.isValid());

  QPixmap pixmap = current.data(AttachmentModel::ImageRole).value<QPixmap>();
  QSize size;
  if (ui->actionFitToScreen->isChecked()) {
    size = viewportSize();
  }
  label_->setPixmap(pixmap, size);
}  // slot_currentRowChanged

void AttachmentDialog::slot_dataChanged(const QModelIndex &topLeft,
                                        const QModelIndex &bottomRight) {
  Q_UNUSED(bottomRight);
  if (!topLeft.isValid()) return;
  slot_currentRowChanged(currentIndex(), QModelIndex());
}  // slot_DataChanged

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

QModelIndexList AttachmentDialog::selectedIndexes() {
  QModelIndexList indexList;
  QItemSelectionModel *selection = ui->listView->selectionModel();
  if (!selection) return indexList;
  indexList = selection->selectedRows();
  return indexList;
}  // selectedIndexes

QModelIndex AttachmentDialog::currentIndex() {
  QItemSelectionModel *selection = ui->listView->selectionModel();
  if (!selection) return QModelIndex();
  QModelIndex current = selection->currentIndex();
  return current;
}  // currentIndex

void AttachmentDialog::internalRotate(RotateDirection direction) {
  QModelIndex current = currentIndex();
  AttachmentModel *model = attachmentModel();
  if (!model) return;

  model->rotateSelected(current, direction);
}  // internalRotate

void AttachmentDialog::enableActions(bool enable) {
    ui->actionRemove->setEnabled(enable);
    ui->actionExport->setEnabled(enable);
    ui->actionRotate90Clockwise->setEnabled(enable);
    ui->actionRotate90Anticlockwise->setEnabled(enable);
}  // enableActions
