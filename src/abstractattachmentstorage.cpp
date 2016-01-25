#include <QtCore/QString>
#include <QtCore/QHash>

#include "abstractattachmentstorage.h"



uint qHash(const AttachedItem &item) { return qHash(item.filename); }