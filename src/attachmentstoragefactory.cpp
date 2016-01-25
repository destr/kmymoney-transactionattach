#include "attachmentstoragefactory.h"
#include "attachmentstoragefilesystem.h"

AbstractAttachmentStorage* AttachmentStorageFactory::create(
    AttachmentStorageFactory::Type type) {
  switch (type) {
    case Filesystem: return new AttachmentStorageFilesystem();
    case Sqlite: return 0;
  }
  return 0;
}  // create
