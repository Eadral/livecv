#include "qmljsbuiltintypes_p.h"
#include "qmljs/qmljsvalueowner.h"

namespace lv{

QmlJsBuiltinTypes::QmlJsBuiltinTypes(){
}

QString QmlJsBuiltinTypes::nameFromCpp(const QString &type){
    QmlJS::ValueOwner* valueowner = new QmlJS::ValueOwner(QmlJS::ValueOwner::sharedValueOwner());

    if (type == QLatin1String("QByteArray")
            || type == QLatin1String("QString")) {
        return "string";
    } else if (type == QLatin1String("QUrl")) {
        return "url";
    } else if (type == QLatin1String("long")) {
        return "long";
    }  else if (type == QLatin1String("float")
                || type == QLatin1String("qreal")) {
        return "double";
    } else if (type == QLatin1String("QFont")) {
        return valueowner->qmlFontObject()->className();
    } else if (type == QLatin1String("QPoint")
            || type == QLatin1String("QPointF")
            || type == QLatin1String("QVector2D")) {
        return valueowner->qmlPointObject()->className();
    } else if (type == QLatin1String("QSize")
            || type == QLatin1String("QSizeF")) {
        return valueowner->qmlSizeObject()->className();
    } else if (type == QLatin1String("QRect")
            || type == QLatin1String("QRectF")) {
        return valueowner->qmlRectObject()->className();
    } else if (type == QLatin1String("QVector3D")) {
        return valueowner->qmlVector3DObject()->className();
    } else if (type == QLatin1String("QColor")) {
        return "color";
    } else if (type == QLatin1String("QDateTime")) {
        return "date";
    }

    return "";
}

}// namespace
