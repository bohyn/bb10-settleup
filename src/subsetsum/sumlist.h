#ifndef SUBSETSUM_LIST_H
#define SUBSETSUM_LIST_H

#include "sum.h"

#include <QList>
#include <QString>

namespace SubSetSum {

class SumList : public QList<Sum>
{
public:
    QString toString() const;
};

}

#endif // SUBSETSUM_LIST_H
