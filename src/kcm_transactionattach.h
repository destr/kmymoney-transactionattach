#pragma once

#include <kcmodule.h>

class KCMTransactionAttach : public KCModule {
public:
    explicit KCMTransactionAttach(QWidget *parent = 0,
                                  const QVariantList &args = QVariantList());
    ~KCMTransactionAttach();
};
