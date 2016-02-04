#pragma once

#include <QtCore/qglobal.h>
#include <QtCore/QSize>
#include <QtGui/QListView>

class ListViewAttachment : public QListView {
  Q_OBJECT
 public:
  explicit ListViewAttachment(QWidget *parent = 0);
  static const QSize previewSize;
  // QWidget interface
 protected:
  void dragEnterEvent(QDragEnterEvent *event);
  void dropEvent(QDropEvent *event);
  void dragMoveEvent(QDragMoveEvent *event);

 private:
  Q_DISABLE_COPY(ListViewAttachment)
};
