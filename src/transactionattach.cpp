#include <QtCore/QDebug>

#include <KDE/KAction>
#include <KDE/KActionCollection>
#include <KDE/KLocale>
#include <KDE/KPluginFactory>
#include <KDE/KPluginInfo>

#include <kmymoney/pluginloader.h>
#include <kmymoney/selectedtransaction.h>
#include <kmymoney/mymoneyfile.h>

#include "attachmentdialog.h"
#include "attachmentmodel.h"
#include "attachmentstoragefactory.h"
#include "pluginsettings.h"
#include "transactionattach.h"

K_PLUGIN_FACTORY(TransactionAttachFactory,
                 registerPlugin<TransactionAttach>(););
K_EXPORT_PLUGIN(TransactionAttachFactory("kmm_transactionattach"))

struct TransactionAttach::Private {
  KAction *action;
  /// selected transaction id
  QString transactionId;
  /// detail transaction info
  QString transactionInfo;
  AttachmentModel model;

  void setModelSettings();
};

TransactionAttach::TransactionAttach(QObject *parent, const QVariantList &args)
    : KMyMoneyPlugin::Plugin(parent, "KMyMoney Transaction Attach"),
      d_(new Private) {
  Q_UNUSED(args)

  setComponentData(TransactionAttachFactory::componentData());
  setXMLFile("kmm_transactionattach.rc");

  qDebug() << "KMyMoney transactionattach plugin loaded";

  d_->action = actionCollection()->addAction("transaction_attachment", this,
                                             SLOT(slotAttachment()));
  d_->action->setText(i18n("Attachment..."));
  d_->action->setEnabled(false);

  KMyMoneyPlugin::PluginLoader *instance =
      KMyMoneyPlugin::PluginLoader::instance();
  connect(instance, SIGNAL(plug(KPluginInfo *)), this,
          SLOT(slotPlug(KPluginInfo *)));
  connect(instance, SIGNAL(unplug(KPluginInfo *)), this,
          SLOT(slotUnplug(KPluginInfo *)));
  connect(instance, SIGNAL(configChanged(Plugin *)), this,
          SLOT(slotConfigChanged(Plugin *)));

  d_->setModelSettings();
}  // Ctor

TransactionAttach::~TransactionAttach() {}  // Dtor

void TransactionAttach::slotPlug(KPluginInfo *info) {
  if (info->name() != objectName()) return;
  connect(
      viewInterface(),
      SIGNAL(transactionsSelected(KMyMoneyRegister::SelectedTransactions)),
      this,
      SLOT(slotTransactionsSelected(KMyMoneyRegister::SelectedTransactions)));
}  // slotPlug

void TransactionAttach::slotUnplug(KPluginInfo *info) {
  if (info->name() != objectName()) return;
  disconnect(
      viewInterface(),
      SIGNAL(transactionsSelected(KMyMoneyRegister::SelectedTransactions)),
      this,
      SLOT(slotTransactionsSelected(KMyMoneyRegister::SelectedTransactions)));
}  // slotUnplug

void TransactionAttach::slotConfigChanged(KMyMoneyPlugin::Plugin *plugin) {
  Q_UNUSED(plugin)
  PluginSettings::self()->readConfig();
  d_->setModelSettings();
}  // slotConfigChanged

void TransactionAttach::slotAttachment() {
  Q_ASSERT(!d_->transactionId.isEmpty());

  d_->model.setTransactionId(d_->transactionId);

  AttachmentDialog d;
  d.setModel(&d_->model);
  d.setTransactionInfo(d_->transactionInfo);
  qDebug() << Q_FUNC_INFO << d_->transactionId;
  d.exec();
}  // slotAttachment

void TransactionAttach::slotTransactionsSelected(
    const KMyMoneyRegister::SelectedTransactions &transactions) {
  /// add attachment only one transaction...
  if (transactions.count() != 1) {
    d_->action->setEnabled(false);
    d_->transactionId.clear();
    return;
  }
  d_->action->setEnabled(true);

  const KMyMoneyRegister::SelectedTransaction &st = transactions.first();
  const MyMoneyTransaction &t = st.transaction();
  if (t.id().isEmpty()) return;
  d_->transactionId = t.id();

  MyMoneyFile *file = MyMoneyFile::instance();

  MyMoneySplit sp = t.splitByAccount(st.split().accountId(), false);
  const QString category = file->accountToCategory(sp.accountId());

  d_->transactionInfo =
      QString(i18n("<b>Transaction:</b> %1 &nbsp; %2 &nbsp; %4: %3")
                  .arg(t.postDate().toString(Qt::DefaultLocaleShortDate))
                  .arg(category)
                  .arg(st.split().shares().abs().toDouble())
                  .arg(t.commodity()));
}  // slotTransactionsSelected

void TransactionAttach::Private::setModelSettings() {
  StorageType type = StorageType(PluginSettings::comboBoxStorageType());

  QString path;
  switch (type) {
    default:
    case Filesystem:
      path = PluginSettings::lineEditDirPath();
      break;
    case Sqlite:
      path = PluginSettings::lineEditSqlitePath();
      break;
  }
  model.setStorageType(type);
  model.setStoragePath(path);
}  // setModelSettings
