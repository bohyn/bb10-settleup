#include "solver.h"
#include "log.h"
#include "statistics.h"

#include <QStringBuilder>

namespace SubSetSum {

Solver::Solver()
{
}

QList<TransactionList> Solver::solve(const IntList &balance)
{
    m_statistics.clear();
    m_statistics.startTimer();
    m_balance = balance;
    QList<TransactionList> ret;
    while(true) {
        int n = 0;
        foreach(const int &x, m_balance)
            if(x > 0)
                n++;
        if(n == 0)
            break;

        splitBalance();
        logDebug() << "credits:" << arrayToString(m_credits);
        logDebug() << "debets:" << arrayToString(m_debets);
        SumList cred_sums = makeSubSetSums(m_credits);
        SumList deb_sums = makeSubSetSums(m_debets);
        logTrash() << cred_sums.length() << "=========== credit sums";
        logTrash() << cred_sums.toString();
        logTrash() << deb_sums.length() << "=========== debet sums";
        logTrash() << deb_sums.toString();
        ret << takeMinimalBalancedTransactions(cred_sums, deb_sums);
    }
    m_statistics.stopTimer();
    return ret;
}

void Solver::splitBalance()
{
    logDebug() << arrayToString(m_balance) << "<-------------- SPLIT BALANCE";
    m_credits.clear();
    m_creditsToBalance.clear();
    m_debets.clear();
    m_debetsToBalance.clear();
    for(int i=0; i<m_balance.length(); i++) {
        Int val = m_balance[i];
        if(val < 0) {
            m_debets << static_cast<UInt>(-val);
            m_debetsToBalance << i;
        }
        else if(val > 0) {
            m_credits << static_cast<UInt>(val);
            m_creditsToBalance << i;
        }
    }
}

SumList Solver::makeSubSetSums_helper(const UIntList &items, int n)
{
    SumList ret;
    if(n == 0) {
        m_statistics.increment(Statistics::KeySubSetSumsGeneratedCount);
        ret << Sum(items);
    }
    else {
        ret = makeSubSetSums_helper(items, n-1);
        foreach(const Sum x, ret) {
            m_statistics.increment(Statistics::KeySubSetSumsGeneratedCount);
            Sum x2 = x;
            x2.addIndex(n-1);
            SumList::iterator it = qLowerBound(ret.begin(), ret.end(), x2);
            if(it < ret.end() && it->sum() == x2.sum()) {
                // item with sum x2.sum() is in result set already
                // ignore x2, because x2.length() > ret[ix].length()
            }
            else {
                ret.insert(it, x2);
            }
        }
    }
    return ret;
}

SumList Solver::makeSubSetSums(const UIntList &items)
{
    return makeSubSetSums_helper(items, items.length());
}

TransactionList Solver::takeMinimalBalancedTransactions(const SumList &credit_sums, const SumList &debet_sums)
{
    int crix = 1; // skip firstzero sum
    int dbix = 1; // skip firstzero sum
    TransactionList ret;
    while(crix<credit_sums.count() && dbix<debet_sums.count()) {
        const Sum &crs = credit_sums[crix];
        const Sum &dbs = debet_sums[dbix];
        logDebug() << "debet " << '[' << dbix << ']' << dbs.toString() << "vs" << "credit" << '[' << crix << ']' << crs.toString();
        if(crs.sum() < dbs.sum())
            crix++;
        else if(crs.sum() > dbs.sum())
            dbix++;
        else {
            int current_transactions_count = ret.count();
            int proposed_transactions_count = crs.length() + dbs.length() - 1;
            if(current_transactions_count == 0 || proposed_transactions_count < current_transactions_count) {
                ret = createTransactions(crs, dbs);
            }
            crix++;
            dbix++;
        }
    }
    Q_ASSERT(!ret.isEmpty());
    {
        // commit transaction
        logDebug() << "*** commit transactions ***";
        foreach(const Transaction &x, ret) {
            logDebug() << x.toString();
            m_balance[x.debetIndex] = 0;
            m_balance[x.creditIndex] = 0;
        }
    }
    return ret;
}

namespace
{
    QString mapToString(const QMultiMap<UInt, int> &map)
    {
        QStringList sl;
        QMapIterator<UInt, int> it(map);
        while (it.hasNext()) {
            it.next();
            sl << QString("%1->%2").arg(it.key()).arg(it.value());
        }
        return '{' % sl.join(", ") % '}';
    }
}

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
namespace
{

const UInt &lastKey(const QMultiMap<UInt, int> &m)
{
    Q_ASSERT(!m.isEmpty());
    return (m.constEnd() - 1).key();
}

}
#endif

// this function is actualy bottle neck
// TODO make faster implementation
TransactionList Solver::createTransactions(const Sum &credit_sum, const Sum &debet_sum)
{
    TransactionList ret;
    logDebug() << "creating transactions for deb:" << debet_sum.toString() << "cre:" << credit_sum.toString();
    QMultiMap<UInt, int> credit_ixs;
    for(int i=0; i<credit_sum.indexMask().size(); i++) {
        if(credit_sum.indexMask().at(i)) {
            credit_ixs.insert(m_credits[i], m_creditsToBalance[i]);
        }
    }
    QMultiMap<UInt, int> debet_ixs;
    for(int i=0; i<debet_sum.indexMask().size(); i++) {
        if(debet_sum.indexMask().at(i)) {
            //qDebug() << "+++" << i << m_debets[i] << "->" << m_debetsToBalance[i];
            debet_ixs.insert(m_debets[i], m_debetsToBalance[i]);
        }
    }
    logTrash() << "deb map:" << mapToString(debet_ixs) << "\t cre map:" << mapToString(credit_ixs);
    while(!credit_ixs.isEmpty() && !debet_ixs.isEmpty()) {
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
        UInt max_cr_value = lastKey(credit_ixs);
        UInt max_db_value = lastKey(debet_ixs);
#else
        UInt max_cr_value = credit_ixs.lastKey();
        UInt max_db_value = debet_ixs.lastKey();
#endif
        int max_cr_index = credit_ixs.take(max_cr_value);
        int max_db_index = debet_ixs.take(max_db_value);
        logTrash() << "\t max db:" << max_db_value << '[' << max_db_index << ']' << "\t max cr:" << max_cr_value << '[' << max_cr_index << ']';
        if(max_cr_value < max_db_value) {
            ret << Transaction(max_db_index, max_cr_index, max_cr_value);
            debet_ixs.insert(max_db_value - max_cr_value, max_db_index);
        }
        else if(max_cr_value > max_db_value) {
            ret << Transaction(max_db_index, max_cr_index, max_db_value);
            credit_ixs.insert(max_cr_value - max_db_value,max_cr_index);
        }
        else {
            ret << Transaction(max_db_index, max_cr_index, max_db_value);
        }
        logTrash() << "deb map:" << mapToString(debet_ixs) << "\t cre map:" << mapToString(credit_ixs);
    }
    Q_ASSERT(credit_ixs.isEmpty());
    Q_ASSERT(debet_ixs.isEmpty());
    return ret;
}

}
