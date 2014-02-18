#include "log.h"

namespace SubSetSum {

Log::Level Log::levelTreshold = Log::Info;

void Log::setLevelTreshold(Log::Level treshold)
{
    levelTreshold = treshold;
}

void Log::write(const QString &msg)
{
    if(!msg.isEmpty()) {
        QTextStream err(stderr, QIODevice::WriteOnly);
        err << msg << '\n';
    }
}

Log logTrash() { return Log(Log::Trash); }
Log logDebug() { return Log(Log::Debug); }
Log logInfo() { return Log(Log::Info); }
Log logWarning() { return Log(Log::Warning); }
Log logError() { return Log(Log::Error); }

}
