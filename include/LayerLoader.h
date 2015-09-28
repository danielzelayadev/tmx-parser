#ifndef LAYERLOADER_H
#define LAYERLOADER_H

#include "TMXLoader.h"

class Map;
class Layer;
class ImageLayer;
class ObjectLayer;

class LayerLoader : public TMXLoader
{
    public:
        LayerLoader(XMLDocument* tmxFile, ErrorHandler* errorHandler):TMXLoader(tmxFile, errorHandler) {};

        friend class TMXParser;

    private:
        bool loadLayerNode(Map* tiledMap, XMLNode* layerNode);
        bool loadLayerAttributes(Layer* layer, XMLElement* element);

        bool loadImageLayerNode(Map* tiledMap, XMLNode* imageLayerNode);
        bool loadImageLayerAttributes(ImageLayer* iLayer, XMLElement* element);

        bool loadObjectGroupNode(Map* tiledMap, XMLNode* objectGroupNode);
        bool loadObjectLayerAttributes(ObjectLayer* oLayer, XMLElement* element);
};

#endif // LAYERLOADER_H
