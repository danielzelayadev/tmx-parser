#ifndef TILELOADER_H
#define TILELOADER_H

#include "TMXLoader.h"

class Tile;

class TileLoader : public TMXLoader
{
    public:
        TileLoader(XMLDocument* tmxFile, ErrorHandler* errorHandler):TMXLoader(tmxFile, errorHandler) {};

        friend class DataLoader;
        friend class TilesetLoader;

    private:
        bool loadTileNode(Tile* tile, XMLNode* tileNode);
        bool loadTileAttributes(Tile* tile, XMLElement* element);

};

#endif // TILELOADER_H