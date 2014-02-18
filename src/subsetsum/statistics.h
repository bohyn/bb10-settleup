#ifndef SUBSETSUM_STATISTICS_H
#define SUBSETSUM_STATISTICS_H

#include <QMap>
#include <QVariant>
#include <QElapsedTimer>

namespace SubSetSum {

class Statistics
{
public:
    enum Key {KeySubSetSumsGeneratedCount, KeyTimeElapsedMs};
public:
    void clear() {
        m_data.clear();
    }
    QVariant value(Key key) {
        return m_data.value(key);
    }
    void setValue(Key key, const QVariant &val) {
        m_data[key] = val;
    }
    void increment(Key key) {
        int n = value(key).toInt();
        setValue(key, ++n);
    }
    void startTimer() {
        m_elapsedTimer.start();
    }
    void stopTimer() {
        qint64 ms = m_elapsedTimer.elapsed();
        setValue(KeyTimeElapsedMs, ms);
    }

    QString toString() const;
private:
    static QString keyToString(Key key);
private:
    QMap<int, QVariant> m_data;
    QElapsedTimer m_elapsedTimer;
};

}

#endif // SUBSETSUM_STATISTICS_H
