#ifndef TMXPARSER_H
#define TMXPARSER_H

#include <tinyxml2.h>
#include <string>
#include <vector>
#include <stdio.h>

#include "MapLoader.h"
#include "ImageLayer.h"
#include "ObjectLayer.h"
#include "RectangleMapObject.h"
#include "EllipseMapObject.h"
#include "PolygonMapObject.h"
#include "PolylineMapObject.h"

#include "ErrorHandler.h"

using namespace tinyxml2;
using std::string;
using std::vector;

class Tile;
class Terrain;

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

        // TILESET LOADER

        bool loadTileSetNode(Map* tiledMap, XMLNode* tilesetNode);
        bool loadTileSetAttributes(Map* tiledMap, XMLElement* element);
        bool loadTileOffsetAttributes(Map* tiledMap, XMLElement* element);

        // IMAGE LOADER

        bool loadImageNode(Image* image, XMLNode* imageNode);
        bool loadImageAttributes(Image* image, XMLElement* element);

        // DATA LOADER

        bool loadDataNode(Data* data, XMLNode* dataNode);
        bool loadDataAttributes(Data* data, XMLElement* element);

        // TILE LOADER

        bool loadTileNode(Tile* tile, XMLNode* tileNode);
        bool loadTileAttributes(Tile* tile, XMLElement* element);

        // PROPERTY LOADER

        bool loadProperties(vector<Property*>* properties, XMLNode* propertiesNode);
        bool loadPropertyAttributes(vector<Property*>* properties, XMLElement* element);

        // TERRAIN LOADER

        bool loadTerrainTypes(vector<Terrain*>* terrains, XMLNode* terraintypeNode);
        bool loadTerrainAttributes(vector<Terrain*>* terrains, XMLElement* element);

        // LAYER LOADER

        bool loadLayerNode(Map* tiledMap, XMLNode* layerNode);
        bool loadLayerAttributes(Layer* layer, XMLElement* element);

        bool loadImageLayerNode(Map* tiledMap, XMLNode* imageLayerNode);
        bool loadImageLayerAttributes(ImageLayer* iLayer, XMLElement* element);

        bool loadObjectGroupNode(Map* tiledMap, XMLNode* objectGroupNode);
        bool loadObjectLayerAttributes(ObjectLayer* oLayer, XMLElement* element);

        // OBJECT LOADER

        bool loadObject(vector<MapObject*>* objects, XMLNode* objectNode);

        bool loadObjectAttributes(MapObject* object, XMLElement* element);

        bool loadRectAttributes(RectangleMapObject* rmo, XMLElement* element);

        bool loadEllipseAttributes(EllipseMapObject* ellipse, XMLElement* element);

        bool loadPolygonAttributes(PolygonMapObject* polygon, XMLElement* element);

        bool loadPolylineAttributes(PolylineMapObject* polyline, XMLElement* element);
};

#endif // TMXPARSER_H
