#include "attachmentstoragefactory.h"
#include "attachmentstorage.h"

AbstractAttachmentStorage* AttachmentStorageFactory::create(
    AttachmentStorageFactory::Type type) {
  switch (type) {
    case Filesystem: return new AttachmentStorage();
    case Sqlite: return 0;
  }
  return 0;
}  // create
