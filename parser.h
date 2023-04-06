#ifndef PARSER_H
#define PARSER_H

#include <QString>

class parser
{
public:
    parser();
    static QString parse(QString line);
};

#endif // PARSER_H
