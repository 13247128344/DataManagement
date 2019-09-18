#pragma once

#include <QtCore/qglobal.h>

# if defined(IVMS_PUBLIC_LIB)
#  define IVMS_PUBLIC_EXPORT Q_DECL_EXPORT
# else
#  define IVMS_PUBLIC_EXPORT Q_DECL_IMPORT
# endif
