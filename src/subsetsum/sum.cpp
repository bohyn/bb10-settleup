#include "sum.h"
#include "log.h"

#include <QStringList>

namespace SubSetSum {

Sum::Sum(const UIntList &item_list)
{
    d = new Data(item_list);
}

void Sum::addIndex(int ix)
{
    Q_ASSERT(ix >= 0 && ix < items().count());
    //qDebug() << Q_FUNC_INFO << ix << "->" << items()[ix];
    //qDebug() << "before:" << toString();
    d->sum += items()[ix];
    d->indexMask.setBit(ix);
    //qDebug() << "after:" << toString();
}

QString Sum::toString() const
{
    QStringList sl;
    IndexMask mask = indexMask();
    for(int i=0; i<indexMask().size(); i++) {
        if(mask.at(i)) {
            sl << QString::number(items()[i]);
        }
        else {
            sl << ".";
        }
    }
    QString ret = "%1:%2 [%3]";
    ret = ret.arg(sum()).arg(length()).arg(sl.join(","));
    return ret;
}

}
