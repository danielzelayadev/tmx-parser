#ifndef TMXLOADER_H
#define TMXLOADER_H

#include <tinyxml2.h>

#include <ErrorHandler.h>

using namespace tinyxml2;

class TMXLoader
{
    public:
        TMXLoader(XMLDocument* tmxFile, ErrorHandler* errorHandler);

        friend class TMXParser;

    protected:
        XMLDocument* tmxFile;
        ErrorHandler* errorHandler;

};

#endif // TMXLOADER_H
