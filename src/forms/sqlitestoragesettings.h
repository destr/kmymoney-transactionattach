#pragma once

#include <QtCore/qglobal.h>
#include <QWidget>

#include "ui_sqlitestoragesettings.h"

class SqliteStorageSettings : public QWidget, public Ui::SqliteStorageSettings {
  Q_OBJECT

 public:
  explicit SqliteStorageSettings(QWidget *parent = 0);
  ~SqliteStorageSettings();

 private:
  Q_DISABLE_COPY(SqliteStorageSettings)
};
