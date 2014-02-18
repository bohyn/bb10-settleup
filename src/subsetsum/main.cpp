#include "subsetsum/solver.h"
#include "subsetsum/log.h"
#include "subsetsum/statistics.h"

#include <QStringBuilder>

void applyTransaction(SubSetSum::IntList &balance, const SubSetSum::Transaction &transaction)
{
    balance[transaction.debetIndex] += transaction.value;
    balance[transaction.creditIndex] -= transaction.value;
}

int main(int argc, char *argv[])
{
    //logTrash() << Q_FUNC_INFO;
    //QCoreApplication a(argc, argv);
    //return a.exec();
    QStringList args;
    for(int i=1; i<argc; i++) {
        QString arg = QString::fromUtf8(argv[i]);
        if(arg == "-v")
            SubSetSum::Log::setLevelTreshold(SubSetSum::Log::Debug);
        else if(arg == "-vv")
            SubSetSum::Log::setLevelTreshold(SubSetSum::Log::Trash);
        else
            args << arg;
    }

    SubSetSum::IntList balance;
    if(args.length() == 0) {
        balance << 1 << 3 << -2 << 5;
    }
    else if(args.length() <= 2) {
        int n = QString(args[0]).toInt() - 1;
        int a = 20;
        if(args.length() == 2)
            a = QString(args[1]).toInt();
        for(int i=0; i<n; i++) {
            int r = qrand() % a - a/2;
            balance << r;
        }
    }
    else {
        for(const auto &x: args)
            balance << x.toInt();
    }

    int sum = 0;
    for(auto x: balance)
        sum += x;
    if(sum != 0)
        balance << -sum;

    SubSetSum::Solver solver;
    QList<SubSetSum::TransactionList> res = solver.solve(balance);

    QTextStream err(stderr, QIODevice::WriteOnly);
    err << "=====================================================" << '\n';
    err << "input balance:" << SubSetSum::Solver::arrayToString(balance) << '\n';
    err << "=====================================================" << '\n';
    err << "solution:" << '\n';
    for(auto l: res) {
        for(auto t: l) {
            applyTransaction(balance, t);
            err << t.toString() << '\t' << SubSetSum::Solver::arrayToString(balance) << '\n';
        }
        err << "--------------------------------------------------" << '\n';
    }
    err << solver.statisticsString() << '\n';
    return 0;
}
