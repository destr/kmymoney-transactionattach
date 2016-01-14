#include <QtGui/QVBoxLayout>
#include <QtCore/QDebug>
// KDE includes
#include <KPluginFactory>

#include "kcm_transactionattach.h"
#include "pluginsettingswidget.h"
#include "pluginsettings.h"

K_PLUGIN_FACTORY(KCMTransactionAttachFactory,
                 registerPlugin<KCMTransactionAttach>();)

K_EXPORT_PLUGIN(KCMTransactionAttachFactory("kmm_transactionattach", "kmymoney"))

KCMTransactionAttach::KCMTransactionAttach(QWidget *parent, const QVariantList &args):
    KCModule(KCMTransactionAttachFactory::componentData(), parent, args) {
    PluginSettingsWidget *w = new PluginSettingsWidget(this);
    addConfig(PluginSettings::self(), w);
    QVBoxLayout *layout(new QVBoxLayout(this));
    setLayout(layout);
    layout->addWidget(w);
    load();
}  // Ctor

KCMTransactionAttach::~KCMTransactionAttach() {
}  // Dtor
