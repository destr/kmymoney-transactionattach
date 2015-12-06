#pragma once
#include <QtCore/qglobal.h>

#if defined(TRANSACTIONATTACH_LIB)
# define TRANSACTIONATTACH_API Q_DECL_EXPORT
#else
# define TRANSACTIONATTACH_API Q_DECL_IMPORT
#endif /* TRANSACTIONATTACH_LIB */
