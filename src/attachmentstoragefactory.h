#pragma once

#include <QtCore/qglobal.h>

class AbstractAttachmentStorage;

class AttachmentStorageFactory {
public:
  enum Type {
    Filesystem,
    Sqlite
  };

  static AbstractAttachmentStorage* create(Type type);

};
