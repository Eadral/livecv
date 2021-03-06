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

#ifndef LVLIVEPALLETE_H
#define LVLIVEPALLETE_H

#include <QObject>
#include <QQuickItem>

#include "live/lveditorglobal.h"
#include "live/codeconverter.h"

namespace lv{

class LV_EDITOR_EXPORT LivePalette : public CodeConverter{

    Q_OBJECT
    Q_PROPERTY(QQuickItem* item READ item  WRITE setItem  NOTIFY itemChanged)
    Q_PROPERTY(QVariant value   READ value WRITE setValue NOTIFY valueChanged)

public:
    explicit LivePalette(QObject *parent = 0);
    virtual ~LivePalette();

    QQuickItem* item();
    void setItem(QQuickItem* item);

    const QVariant &value() const;
    void setValue(const QVariant& value);

    void initPallete(const QVariant &value);
    void setValueFromCode(const QVariant& value);

signals:
    void itemChanged();
    void valueChanged();

    void init(const QVariant& value);
    void codeChanged(const QVariant& value);

private:
    Q_DISABLE_COPY(LivePalette)

    bool        m_codeChange;
    QQuickItem* m_item;
    QVariant    m_value;
};

inline QQuickItem *LivePalette::item(){
    return m_item;
}

inline void LivePalette::setItem(QQuickItem *item){
    if (m_item == item)
        return;

    m_item = item;
    emit itemChanged();
}

inline const QVariant& LivePalette::value() const{
    return m_value;
}

inline void LivePalette::setValue(const QVariant &value){
    if ( (value.canConvert<QObject*>() || m_value != value) && !m_codeChange ){
        m_value = value;
        emit valueChanged();
    }
}

}// namespace

#endif // LVLIVEPALLETE_H
