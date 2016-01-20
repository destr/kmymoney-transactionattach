#include <QtCore/QDebug>
#include <QtCore/QUrl>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QDropEvent>

#include "attachdelegate.h"
#include "attachmentmodel.h"
#include "listviewattachment.h"

/// ориентация А6 портретная
const QSize ListViewAttachment::previewSize(105, 148);

ListViewAttachment::ListViewAttachment(QWidget* parent)
    : QListView(parent) {
  setAcceptDrops(true);
  setItemDelegate(new AttachDelegate(this));
  setMaximumWidth(200);
}  // Ctor

void ListViewAttachment::dragEnterEvent(QDragEnterEvent* event) {
  if (!event->mimeData()->hasUrls()) return;

  event->acceptProposedAction();
}  // dragEnterEvent

void ListViewAttachment::dropEvent(QDropEvent* event) {
  event->acceptProposedAction();
  AttachmentModel *model = qobject_cast<AttachmentModel*>(this->model());
  if (!model) return;

  QStringList list;
  Q_FOREACH(const QUrl &url, event->mimeData()->urls()) {
    if (url.isLocalFile()) {
      list.push_back(url.toLocalFile());
    }
  }

  model->addFiles(list);
}  // dropEvent

void ListViewAttachment::dragMoveEvent(QDragMoveEvent* event) {
  event->acceptProposedAction();
}  // dragMoveEvent
