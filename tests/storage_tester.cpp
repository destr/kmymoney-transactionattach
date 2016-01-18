#include <QtCore/QDebug>
#include <QtGui/QApplication>

#include <src/forms/attachmentdialog.h>
#include <src/attachmentstorage.h>
#include <src/attachmentmodel.h>

int main(int argc, char **argv) {

  QApplication apl(argc, argv);

  AttachmentStorage storage;
  storage.setTransactionId("T0001");

  AttachmentDialog d;
  d.setModel(storage.model());

  d.show();
  return apl.exec();
}
