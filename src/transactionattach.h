#pragma once

#include <QtCore/qglobal.h>
#include <QtCore/QObject>
#include <QtCore/QVariantList>

#include <kmymoney/kmymoneyplugin.h>

#include "transactionattach_export.h"

class TRANSACTIONATTACH_API TransactionAttach : public KMyMoneyPlugin::Plugin {
    Q_OBJECT
public:
    TransactionAttach(QObject *parent, const QVariantList &args);
    ~TransactionAttach();
private:
    Q_DISABLE_COPY(TransactionAttach)
};
