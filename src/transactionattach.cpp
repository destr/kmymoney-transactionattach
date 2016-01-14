#include <QtCore/QDebug>

#include <KDE/KAction>
#include <KDE/KActionCollection>
#include <KDE/KLocale>
#include <KDE/KPluginFactory>
#include <KDE/KPluginInfo>

#include <kmymoney/pluginloader.h>
#include <kmymoney/selectedtransaction.h>

#include "attachmentdialog.h"
#include "transactionattach.h"

K_PLUGIN_FACTORY(TransactionAttachFactory, registerPlugin<TransactionAttach>(););
K_EXPORT_PLUGIN(TransactionAttachFactory("kmm_transactionattach"))

struct TransactionAttach::Private {
    KAction *action;
    /// selected transaction id
    QString transactionId;
};

TransactionAttach::TransactionAttach(QObject *parent, const QVariantList &args)
    : KMyMoneyPlugin::Plugin(parent, "KMyMoney Transaction Attach"), d_(new Private) {

    Q_UNUSED(args)

    setComponentData(TransactionAttachFactory::componentData());
    setXMLFile("kmm_transactionattach.rc");

    qDebug()  << "KMyMoney transactionattach plugin loaded";

    d_->action = actionCollection()->addAction("transaction_attachment", this,
                                               SLOT(slotAttachment()));
    d_->action->setText(i18n("Attachment..."));
    d_->action->setEnabled(false);

    KMyMoneyPlugin::PluginLoader *instance = KMyMoneyPlugin::PluginLoader::instance();
    connect(instance, SIGNAL(plug(KPluginInfo*)), this, SLOT(slotPlug(KPluginInfo*)));
    connect(instance, SIGNAL(unplug(KPluginInfo*)), this, SLOT(slotUnplug(KPluginInfo*)));

}  // Ctor

TransactionAttach::~TransactionAttach() {
}  // Dtor

void TransactionAttach::slotPlug(KPluginInfo *info) {
    if (info->name() != objectName()) return;
    connect(viewInterface(), SIGNAL(transactionsSelected(KMyMoneyRegister::SelectedTransactions)),
        this, SLOT(slotTransactionsSelected(KMyMoneyRegister::SelectedTransactions)));
}  // slotPlug

void TransactionAttach::slotUnplug(KPluginInfo *info) {
    if (info->name() != objectName()) return;
    disconnect(viewInterface(), SIGNAL(transactionsSelected(KMyMoneyRegister::SelectedTransactions)),
        this, SLOT(slotTransactionsSelected(KMyMoneyRegister::SelectedTransactions)));
}  // slotUnplug

void TransactionAttach::slotAttachment() {
    Q_ASSERT(!d_->transactionId.isEmpty());

    AttachmentDialog d;
    qDebug() << Q_FUNC_INFO << d_->transactionId;
    d.exec();
}  // slotAttachment

void TransactionAttach::slotTransactionsSelected(const KMyMoneyRegister::SelectedTransactions &transactions) {
    /// add attachment only one transaction...
    if (transactions.count() != 1) {
        d_->action->setEnabled(false);
        d_->transactionId.clear();
        return;
    }
    d_->action->setEnabled(true);

    const MyMoneyTransaction &t = transactions.first().transaction();
    d_->transactionId = t.id();
}  // slotTransactionsSelected
