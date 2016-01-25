#pragma once

#include <QtCore/qglobal.h>
#include <QtCore/QAbstractItemModel>
#include <QtGui/QDialog>


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

 public slots:
  void addAttachment();
  void removeAttachment();
  void fitToScreen(bool checked);

 private slots:
  void slot_currentRowChanged(const QModelIndex &current,
                            const QModelIndex &previous);
  void accepted();
  void rejected();

private:
  AttachmentModel* attachmentModel();
  QSize viewportSize() const;

 private:
  Ui::AttachmentDialog *ui;
  AspectRatioPixmapLabel *label_;

 private:
  Q_DISABLE_COPY(AttachmentDialog)
};
