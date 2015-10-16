#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H

#include "TMXLoader.h"

#include <vector>

using std::vector;

class MapObject;
class RectangleMapObject;
class EllipseMapObject;
class PolygonMapObject;
class PolylineMapObject;

class ObjectLoader : public TMXLoader
{
    public:
        ObjectLoader(XMLDocument* tmxFile, Map* map, ErrorHandler* errorHandler):TMXLoader(tmxFile, map, errorHandler) {};

        friend class LayerLoader;

    private:
        bool loadObject(vector<MapObject*>* objects, XMLNode* objectNode);

        bool loadObjectAttributes(MapObject* object, XMLElement* element);

        bool loadRectAttributes(RectangleMapObject* rmo, XMLElement* element);

        bool loadEllipseAttributes(EllipseMapObject* ellipse, XMLElement* element);

        bool loadPolygonAttributes(PolygonMapObject* polygon, XMLElement* element);

        bool loadPolylineAttributes(PolylineMapObject* polyline, XMLElement* element);
};

#endif // OBJECTLOADER_H
