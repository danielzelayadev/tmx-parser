#ifndef TILESETLOADER_H
#define TILESETLOADER_H

#include "TMXLoader.h"

class Map;

class TilesetLoader : public TMXLoader
{
    public:
        TilesetLoader(XMLDocument* tmxFile, ErrorHandler* errorHandler):TMXLoader(tmxFile, errorHandler) {};

        friend class TMXParser;

    private:
        bool loadTileSetNode(Map* tiledMap, XMLNode* tilesetNode);
        bool loadTileSetAttributes(Map* tiledMap, XMLElement* element);
        bool loadTileOffsetAttributes(Map* tiledMap, XMLElement* element);
};

#endif // TILESETLOADER_H
