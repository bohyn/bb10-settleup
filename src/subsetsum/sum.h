#ifndef SUBSETSUM_SUM_H
#define SUBSETSUM_SUM_H

#include "subsetsum.h"

#include <QSharedData>
#include <QList>
#include <QBitArray>

namespace SubSetSum {

class Sum
{
public:
    typedef QBitArray IndexMask;
private:
    class Data : public QSharedData
    {
    public:
        Data(const UIntList &item_list) : sum(0), items(item_list)
        {
            indexMask = QBitArray(items.length());
        }
    public:
        IndexMask indexMask;
        UInt sum;
        UIntList items;
    };
    QSharedDataPointer<Data> d;
public:
    Sum(const UIntList &item_list = UIntList());

    void addIndex(int ix);
    QString toString() const;

    bool operator<(const Sum &other) const
    {
        return this->sum() < other.sum();
    }
public:
    const UIntList& items() const {return d->items;}
    UInt sum() const {return d->sum;}
    //void setSum(UInt s) {d->sum = s;}
    IndexMask indexMask() const {return d->indexMask;}
    int length() const {return d->indexMask.count(true);}
};

}

#endif // SUBSETSUM_SUM_H
