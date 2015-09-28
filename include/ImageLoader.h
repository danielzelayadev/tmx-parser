#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include "TMXLoader.h"

class Image;

class ImageLoader : public TMXLoader
{
    public:
        ImageLoader(XMLDocument* tmxFile, ErrorHandler* errorHandler):TMXLoader(tmxFile, errorHandler) {};

        friend class TilesetLoader;
        friend class LayerLoader;
        friend class ObjectLoader;

    private:
        bool loadImageNode(Image* image, XMLNode* imageNode);
        bool loadImageAttributes(Image* image, XMLElement* element);

};

#endif // IMAGELOADER_H
