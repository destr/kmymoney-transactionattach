#include <KDE/KLocale>

#include "pluginsettingswidget.h"
#include "../attachmentstoragefactory.h"

PluginSettingsWidget::PluginSettingsWidget(QObject *parent) {
  Q_UNUSED(parent)
  setupUi(this);
  kcfg_comboBoxStorageType->addItem(i18n("Filesystem"));
  kcfg_comboBoxStorageType->addItem(i18n("Sqlite"));

  connect(kcfg_comboBoxStorageType, SIGNAL(currentIndexChanged(int)),
          stackedWidget, SLOT(setCurrentIndex(int)));
}  // Ctor
