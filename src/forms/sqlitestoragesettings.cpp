#include <KDE/KFileDialog>
#include <KDE/KLocale>

#include "sqlitestoragesettings.h"

SqliteStorageSettings::SqliteStorageSettings(QWidget *parent)
    : QWidget(parent) {
  setupUi(this);

  connect(pushButtonBrowse, SIGNAL(clicked()), this, SLOT(selectPath()));

}  // Ctor

SqliteStorageSettings::~SqliteStorageSettings() {}

void SqliteStorageSettings::selectPath() {
  QString path = KFileDialog::getSaveFileName(
      KUrl(), QString("*.db"), this, i18n("Select attachments storage"), 0);
  if (path.isEmpty()) return;
  kcfg_lineEditSqlitePath->setText(path);
}  // selectPath
