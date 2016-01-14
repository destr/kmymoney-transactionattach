#pragma once

#include <QtCore/qglobal.h>
#include <QtCore/QObject>
#include <QtCore/QScopedPointer>
#include <QtCore/QVariantList>

#include <kmymoney/kmymoneyplugin.h>

#include "transactionattach_export.h"

class KPluginInfo;

class TRANSACTIONATTACH_API TransactionAttach : public KMyMoneyPlugin::Plugin {
    Q_OBJECT
public:
    TransactionAttach(QObject *parent, const QVariantList &args);
    ~TransactionAttach();


private slots:
    void slotPlug(KPluginInfo *info);
    void slotUnplug(KPluginInfo *info);
    void slotAttachment();
    void slotTransactionsSelected(const KMyMoneyRegister::SelectedTransactions &transactions);

private:
    struct Private;
    QScopedPointer<Private> d_;
private:
    Q_DISABLE_COPY(TransactionAttach)
};
