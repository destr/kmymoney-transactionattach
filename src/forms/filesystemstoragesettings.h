#pragma once

#include <QtCore/qglobal.h>
#include <QWidget>

#include "ui_filesystemstoragesettings.h"

class FilesystemStorageSettings : public QWidget,
                                  public Ui::FilesystemStorageSettings {
  Q_OBJECT

 public:
  explicit FilesystemStorageSettings(QWidget *parent = 0);
  ~FilesystemStorageSettings();

 private slots:
  void selectPath();

 private:
  Q_DISABLE_COPY(FilesystemStorageSettings)
};
