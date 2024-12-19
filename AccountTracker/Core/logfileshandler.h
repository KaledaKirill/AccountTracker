#ifndef LOGFILESHANDLER_H
#define LOGFILESHANDLER_H

#include "Parser/ilogparser.h"
#include ""

#include <QScopedPointer>

class LogFilesHandler
{
public:
    LogFilesHandler();

private:
    QScopedPointer<ILogParser> _parser;


};

#endif
