#include <QtCore/QDebug>

#include <KDE/KPluginFactory>

#include "transactionattach.h"

K_PLUGIN_FACTORY(TransactionAttachFactory, registerPlugin<TransactionAttach>(););
K_EXPORT_PLUGIN(TransactionAttachFactory("kmm_transactionattach"))

TransactionAttach::TransactionAttach(QObject *parent, const QVariantList &args)
    : KMyMoneyPlugin::Plugin(parent, "KMyMoney Transaction Attach") {

    setComponentData(TransactionAttachFactory::componentData());
    setXMLFile("kmm_transactionattach.rc");

    qDebug()  << "KMyMoney transactionattach plugin loaded";
}  // Ctor

TransactionAttach::~TransactionAttach() {

}

