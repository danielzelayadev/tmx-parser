#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include "TMXLoader.h"

class Image;

class ImageLoader : public TMXLoader
{
    public:
        ImageLoader(XMLDocument* tmxFile, Map* map, ErrorHandler* errorHandler):TMXLoader(tmxFile, map, errorHandler) {};

        friend class TilesetLoader;
        friend class LayerLoader;
        friend class ObjectLoader;

    private:
        bool loadImageNode(Image* image, XMLNode* imageNode);
        bool loadImageAttributes(Image* image, XMLElement* element);

};

#endif // IMAGELOADER_H
