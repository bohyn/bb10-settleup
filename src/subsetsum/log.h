#ifndef SUBSETSUM_LOG_H
#define SUBSETSUM_LOG_H

#include <QTextStream>

namespace SubSetSum {

class Log
{
public:
    enum Level {Fatal = 0, Error, Warning, Info, Debug, Trash};
private:
    struct Stream {
        //Stream(QIODevice *device) : ts(device), ref(1), type(QtDebugMsg), space(true), message_output(false) {}
        //Stream(QString *string) : ts(string, QIODevice::WriteOnly), ref(1), type(QtDebugMsg), space(true), message_output(false) {}
        Stream(Level l) : ts(&buffer, QIODevice::WriteOnly), ref(1), level(l), space(true) {}
        QTextStream ts;
        QString buffer;
        int ref;
        Level level;
        bool space;
        //bool message_output;
        //QMessageLogContext context;
    } *stream;
private:
    inline bool checkLevel() {return stream->level <= levelTreshold;}
    void write(const QString &msg);
public:
    inline Log(Level l) : stream(new Stream(l)) {}
    inline Log(const Log &o):stream(o.stream) { ++stream->ref; }
    ~Log() {
        if (!--stream->ref) {
            if (stream->space && stream->buffer.endsWith(QLatin1Char(' ')))
                stream->buffer.chop(1);
            write(stream->buffer);
            delete stream;
        }
    }

    static void setLevelTreshold(Level treshold);

    inline Log &space() { stream->space = true; stream->ts << ' '; return *this; }
    inline Log &nospace() { stream->space = false; return *this; }
    inline Log &maybeSpace() { if(checkLevel()) if (stream->space) stream->ts << ' '; return *this; }

    inline Log &operator<<(QChar t) { if(checkLevel()) stream->ts << '\'' << t << '\''; return maybeSpace(); }
    inline Log &operator<<(bool t) { if(checkLevel()) stream->ts << (t ? "true" : "false"); return maybeSpace(); }
    inline Log &operator<<(char t) { if(checkLevel()) stream->ts << t; return maybeSpace(); }
    inline Log &operator<<(signed short t) { if(checkLevel()) stream->ts << t; return maybeSpace(); }
    inline Log &operator<<(unsigned short t) { if(checkLevel()) stream->ts << t; return maybeSpace(); }
    inline Log &operator<<(signed int t) { if(checkLevel()) stream->ts << t; return maybeSpace(); }
    inline Log &operator<<(unsigned int t) { if(checkLevel()) stream->ts << t; return maybeSpace(); }
    inline Log &operator<<(signed long t) { if(checkLevel()) stream->ts << t; return maybeSpace(); }
    inline Log &operator<<(unsigned long t) { if(checkLevel()) stream->ts << t; return maybeSpace(); }
    inline Log &operator<<(qint64 t) { if(checkLevel()) stream->ts << QString::number(t); return maybeSpace(); }
    inline Log &operator<<(quint64 t) { if(checkLevel()) stream->ts << QString::number(t); return maybeSpace(); }
    inline Log &operator<<(float t) { if(checkLevel()) stream->ts << t; return maybeSpace(); }
    inline Log &operator<<(double t) { if(checkLevel()) stream->ts << t; return maybeSpace(); }
    inline Log &operator<<(const char* t) { if(checkLevel()) stream->ts << QString::fromUtf8(t); return maybeSpace(); }
    inline Log &operator<<(const QString & t) { if(checkLevel()) stream->ts << '\"' << t  << '\"'; return maybeSpace(); }
    inline Log &operator<<(QLatin1String t) { if(checkLevel()) stream->ts << '\"'  << t << '\"'; return maybeSpace(); }
    inline Log &operator<<(const QByteArray & t) { if(checkLevel()) stream->ts  << '\"' << t << '\"'; return maybeSpace(); }
    inline Log &operator<<(const void * t) { if(checkLevel()) stream->ts << t; return maybeSpace(); }
private:
    static Level levelTreshold;
};

Log logTrash();
Log logDebug();
Log logInfo();
Log logWarning();
Log logError();

}

#endif // SUBSETSUM_LOG_H
