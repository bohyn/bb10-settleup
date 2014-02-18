#include "statistics.h"

#include <QStringList>

namespace SubSetSum {

QString Statistics::toString() const
{
    QStringList sl;
    QMapIterator<int, QVariant> it(m_data);
    while (it.hasNext()) {
        it.next();
        sl << QString("%1:\t%2").arg(keyToString((Key)it.key())).arg(it.value().toString());
    }
    return sl.join("\n");
}

QString Statistics::keyToString(Statistics::Key key)
{
    QString ret;
    switch(key) {
    case KeySubSetSumsGeneratedCount:ret = "subset sums generated"; break;
    case KeyTimeElapsedMs:ret = "time elapsed [msec]"; break;
    default:
        ret = QString("Unknown key [%1]").arg((int)key);
        break;
    }
    return ret;
}

}
