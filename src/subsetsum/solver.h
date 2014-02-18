#ifndef SUBSETSUM_SOLVER_H
#define SUBSETSUM_SOLVER_H

#include "sum.h"
#include "transaction.h"
#include "sumlist.h"
#include "statistics.h"

#include <QStringList>
#include <QStringBuilder>

namespace SubSetSum {

class Solver
{
public:
    Solver();
public:
    QList<TransactionList> solve(const IntList &balance);
    QString statisticsString() {
        return m_statistics.toString();
    }

    template<class T>
    static QString arrayToString(const QList<T> &list)
    {
        QStringList sl;
        foreach(const T &x, list) {
            sl << QString::number(x);
        }
        return '[' % sl.join(",") % ']';
    }
private:
    void splitBalance();

    SumList makeSubSetSums_helper(const UIntList &items, int n);
    SumList makeSubSetSums(const UIntList &items);
    TransactionList takeMinimalBalancedTransactions(const SumList &credit_sums, const SumList &debet_sums);
    TransactionList createTransactions(const Sum &credit_sum, const Sum &debet_sum);
private:
    IntList m_balance;
    UIntList m_credits;
    UIntList m_debets;
    IndexList m_creditsToBalance;
    IndexList m_debetsToBalance;
    Statistics m_statistics;
};

}

#endif // SUBSETSUM_SOLVER_H
