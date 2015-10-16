#ifndef MAPLOADER_H
#define MAPLOADER_H

#include "TMXLoader.h"

class Map;

class MapLoader : public TMXLoader
{
    public:
        MapLoader(XMLDocument* tmxFile, Map* map, ErrorHandler* errorHandler):TMXLoader(tmxFile, map, errorHandler) {};

        friend class TMXParser;

    private:
        bool loadMapAttributes(Map* tiledMap, XMLElement* element);

};

#endif // MAPLOADER_H
