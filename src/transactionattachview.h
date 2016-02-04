#pragma once

#include <QtCore/qglobal.h>

#include <kmymoney/viewinterface.h>

#include "transactionattach_export.h"

class TRANSACTIONATTACH_API TransactionAttachView : public KMyMoneyPlugin::ViewInterface {
    Q_OBJECT
public:
    TransactionAttachView(QObject *parent);


private:
    Q_DISABLE_COPY(TransactionAttachView)
};
