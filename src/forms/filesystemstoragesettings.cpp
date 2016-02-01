#include <KDE/KFileDialog>
#include <KDE/KLocale>

#include "filesystemstoragesettings.h"

FilesystemStorageSettings::FilesystemStorageSettings(QWidget *parent)
    : QWidget(parent) {
  setupUi(this);

  connect(pushButtonBrowse, SIGNAL(clicked()), this, SLOT(selectPath()));

}  // Ctor

FilesystemStorageSettings::~FilesystemStorageSettings() {}

void FilesystemStorageSettings::selectPath() {
  QString dir = KFileDialog::getExistingDirectory(
      KUrl(), this, i18n("Select attachments storage"));
  if (dir.isEmpty()) return;

  kcfg_lineEditDirPath->setText(dir);
}  // selectPath
