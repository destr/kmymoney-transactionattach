#pragma once

#include <QtCore/qglobal.h>
#include <QtCore/QSize>
#include <QtGui/QListView>

#include "attachmentstorage.h"

class ListViewAttachment : public QListView {
  Q_OBJECT
 public:
  explicit ListViewAttachment(QWidget *parent = 0);

  void setStorage(AttachmentStorage *storage);

  static const QSize previewSize;

  // QWidget interface
 protected:
  void dragEnterEvent(QDragEnterEvent *event);
  void dropEvent(QDropEvent *event);
  void dragMoveEvent(QDragMoveEvent *event);

 private:
  AttachmentStorage *storage_;

 private:
  Q_DISABLE_COPY(ListViewAttachment)
};
