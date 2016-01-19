#include <QtCore/QDebug>
#include <QtCore/QUrl>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QDropEvent>

#include "attachdelegate.h"
#include "listviewattachment.h"

/// ориентация А6 портретная
const QSize ListViewAttachment::previewSize(105, 148);

ListViewAttachment::ListViewAttachment(QWidget* parent)
    : QListView(parent), storage_(0) {
  setAcceptDrops(true);
  setItemDelegate(new AttachDelegate(this));
}  // Ctor

void ListViewAttachment::setStorage(AttachmentStorage* storage) {
  storage_ = storage;
}  // setStorage

void ListViewAttachment::dragEnterEvent(QDragEnterEvent* event) {
  if (!event->mimeData()->hasUrls()) return;

  event->acceptProposedAction();
}  // dragEnterEvent

void ListViewAttachment::dropEvent(QDropEvent* event) {
  event->acceptProposedAction();
  storage_->addFiles(event->mimeData()->urls());
}  // dropEvent

void ListViewAttachment::dragMoveEvent(QDragMoveEvent* event) {
  event->acceptProposedAction();
}  // dragMoveEvent
