#pragma once

#include <QtCore/qglobal.h>

class AbstractAttachmentStorage;

enum StorageType {
  Filesystem,
  Sqlite
};

class AttachmentStorageFactory {
public:
  static AbstractAttachmentStorage* create(StorageType type);

};
