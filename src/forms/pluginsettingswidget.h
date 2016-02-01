#pragma once

#include <QtCore/qglobal.h>

#include "ui_pluginsettingsdecl.h"

class PluginSettingsWidget : public QWidget, public Ui::PluginSettingsDecl {
  Q_OBJECT
 public:
  explicit PluginSettingsWidget(QObject *parent);

 private:
  Q_DISABLE_COPY(PluginSettingsWidget)
};
