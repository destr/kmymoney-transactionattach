#include <QtCore/qglobal.h>
#include <QtCore/QDebug>
#include <QtGui/QApplication>

#include <src/forms/attachmentdialog.h>
#include <src/attachmentstoragefilesystem.h>
#include <src/attachmentmodel.h>

int main(int argc, char **argv) {

  QApplication apl(argc, argv);

  AttachmentModel model;
#if defined(Q_OS_WIN)
  model.setStoragePath("R:/attach");
#else
  model.setStoragePath("/tmp/attach");
#endif
  model.setTransactionId("T0001");

  AttachmentDialog d;
  d.setModel(&model);

  d.show();
  return apl.exec();
}
