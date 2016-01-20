#pragma once

#include <QtCore/qglobal.h>
#include <QtCore/QAbstractItemModel>
#include <QtGui/QDialog>

#include "attachmentstorage.h"

namespace Ui {
class AttachmentDialog;
}

class AspectRatioPixmapLabel;

class AttachmentDialog : public QDialog {
  Q_OBJECT

 public:
  explicit AttachmentDialog(QWidget *parent = 0);
  ~AttachmentDialog();

  void setModel(QAbstractItemModel *model);

 public slots:
  void addAttachment();
  void removeAttachment();
  void fitToScreen(bool checked);

 private slots:
  void slot_currentRowChanged(const QModelIndex &current,
                            const QModelIndex &previous);

  AttachmentModel* attachmentModel();

 private:
  Ui::AttachmentDialog *ui;
  AspectRatioPixmapLabel *label_;

 private:
  Q_DISABLE_COPY(AttachmentDialog)
};
