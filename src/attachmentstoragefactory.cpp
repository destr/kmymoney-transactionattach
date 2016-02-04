#include "attachmentstoragefactory.h"
#include "attachmentstoragefilesystem.h"
#include "attachmentstoragesqlite.h"

AbstractAttachmentStorage* AttachmentStorageFactory::create(StorageType type) {
  switch (type) {
    case Filesystem:
      return new AttachmentStorageFilesystem();
    case Sqlite:
      return new AttachmentStorageSqlite();
  }
  return 0;
}  // create
