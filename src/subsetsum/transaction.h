#ifndef SUBSETSUM_TRANSACTION_H
#define SUBSETSUM_TRANSACTION_H

#include "sum.h"

namespace SubSetSum {

class Transaction
{
public:
    Transaction(int dx = -1, int cx = -1, UInt v = 0);
public:
    QString toString() const;
public:
    int debetIndex;
    int creditIndex;
    UInt value;
};

typedef QList<Transaction> TransactionList;

}

#endif // SUBSETSUM_TRANSACTION_H
