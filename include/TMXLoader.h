#ifndef TMXLOADER_H
#define TMXLOADER_H

#include <tinyxml2.h>

#include <ErrorHandler.h>

class Map;

using namespace tinyxml2;

class TMXLoader
{
    public:
        TMXLoader(XMLDocument* tmxFile, Map* map, ErrorHandler* errorHandler);

        friend class TMXParser;

    protected:
        XMLDocument* tmxFile;
        Map* map;
        ErrorHandler* errorHandler;

};

#endif // TMXLOADER_H
