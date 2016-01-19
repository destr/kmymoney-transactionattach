#pragma once

#include <QtCore/qglobal.h>
#include <QtCore/QAbstractItemModel>
#include <QtGui/QDialog>
#include <QtGui/QLabel>

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

 public slots:
  void addAttachment();
  void removeAttachment();

 private slots:
  void slot_currentRowChanged(const QModelIndex &current,
                            const QModelIndex &previous);

 private:
  Ui::AttachmentDialog *ui;
  QLabel *label_;

 private:
  Q_DISABLE_COPY(AttachmentDialog)
};
