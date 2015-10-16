#ifndef PROPERTYLOADER_H
#define PROPERTYLOADER_H

#include "TMXLoader.h"

#include <vector>

using std::vector;

class Property;

class PropertyLoader : public TMXLoader
{
    public:
        PropertyLoader(XMLDocument* tmxFile, Map* map, ErrorHandler* errorHandler):TMXLoader(tmxFile, map, errorHandler) {};

        friend class TileLoader;
        friend class TMXParser;
        friend class TilesetLoader;
        friend class LayerLoader;
        friend class ObjectLoader;

    private:
        bool loadProperties(vector<Property*>* properties, XMLNode* propertiesNode);
        bool loadPropertyAttributes(vector<Property*>* properties, XMLElement* element);
};

#endif // PROPERTYLOADER_H
