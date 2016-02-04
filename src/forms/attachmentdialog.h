#pragma once

#include <QtCore/qglobal.h>
#include <QtCore/QAbstractItemModel>
#include <QtGui/QDialog>

#include "../abstractattachmentstorage.h"

namespace Ui {
class AttachmentDialog;
}

class AttachmentModel;
class AspectRatioPixmapLabel;

class AttachmentDialog : public QDialog {
  Q_OBJECT

 public:
  explicit AttachmentDialog(QWidget *parent = 0);
  ~AttachmentDialog();

  void setModel(QAbstractItemModel *model);
  void setTransactionInfo(const QString &info);

 public slots:
  void addAttachment();
  void removeAttachment();
  void fitToScreen(bool checked);
  void exportAttachment();
  void rotate90Clockwise();
  void rotate90Anticlockwise();

 private slots:
  void slot_currentRowChanged(const QModelIndex &current,
                            const QModelIndex &previous);
  void slot_dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
  void accepted();
  void rejected();

private:
  AttachmentModel* attachmentModel();
  QSize viewportSize() const;
  QModelIndexList selectedIndexes();
  QModelIndex currentIndex();
  void internalRotate(RotateDirection direction);

 private:
  Ui::AttachmentDialog *ui;
  AspectRatioPixmapLabel *label_;

 private:
  Q_DISABLE_COPY(AttachmentDialog)
};
