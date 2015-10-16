#ifndef TERRAINLOADER_H
#define TERRAINLOADER_H

#include "TMXLoader.h"

#include <vector>

using std::vector;

class Terrain;

class TerrainLoader : public TMXLoader
{
    public:
        TerrainLoader(XMLDocument* tmxFile, Map* map, ErrorHandler* errorHandler):TMXLoader(tmxFile, map, errorHandler) {};

        friend class TilesetLoader;

    private:
        bool loadTerrainTypes(vector<Terrain*>* terrains, XMLNode* terraintypeNode);
        bool loadTerrainAttributes(vector<Terrain*>* terrains, XMLElement* element);
};

#endif // TERRAINLOADER_H
