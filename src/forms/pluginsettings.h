#pragma once

#include "ui_pluginsettingsdecl.h"

class PluginSettingsWidget: public QWidget, public Ui::PluginSettingsDecl {
    Q_OBJECT
public:
    explicit PluginSettingsWidget(QObject *parent);
};
