/****************************************************************************
**
** Copyright (C) 2014-2017 Dinu SV.
** (contact: mail@dinusv.com)
** This file is part of Live CV Application.
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
****************************************************************************/

#ifndef LVQMLJSPARSERGLOBAL_H
#define LVQMLJSPARSERGLOBAL_H

#include <qglobal.h>

#ifndef LV_EDITQMLJS_STATIC
#  ifdef LV_EDITQMLJS_LIB
#    define LV_EDITQMLJS_EXPORT Q_DECL_EXPORT
#  else
#    define LV_EDITQMLJS_EXPORT Q_DECL_IMPORT
#  endif
#else
#  define LV_EDITQMLJS_EXPORT
#endif

#endif // LVQMLJSPARSERGLOBAL_H
