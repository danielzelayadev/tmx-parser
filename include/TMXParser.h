#ifndef TMXPARSER_H
#define TMXPARSER_H

#include <tinyxml2.h>
#include <string>

#include "ErrorHandler.h"

using namespace tinyxml2;
using std::string;

class Map;

class TMXParser
{
    public:
        TMXParser(string fileDir);
        TMXParser();
        ~TMXParser();

        Map* parse();
        Map* parse(string fileDir);

        char* getError();

    private:

        XMLDocument* tmxFile;
        string fileDir;

        ErrorHandler errorHandler;
};

#endif // TMXPARSER_H
