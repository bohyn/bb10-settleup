#include "transaction.h"
#include "log.h"

#include <QString>

namespace SubSetSum {

Transaction::Transaction(int dx, int cx, UInt v)
    : debetIndex(dx), creditIndex(cx), value(v)
{
    logTrash() << "new Trasaction - amount:" << value << ' ' << debetIndex << "->" << creditIndex;
}

QString Transaction::toString() const
{
    QString ret = "amount: %3 from: %1 to: %2";
    return ret.arg(debetIndex).arg(creditIndex).arg(value);
}

}
