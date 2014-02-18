#include "sumlist.h"

#include <QStringList>
#include <QStringBuilder>

namespace SubSetSum {

QString SumList::toString() const
{
    QStringList sl;
    foreach(const Sum &x, *this) {
        sl << x.toString();
    }
    return '[' % sl.join(",") % ']';
}

}
