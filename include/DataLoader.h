#ifndef DATALOADER_H
#define DATALOADER_H

#include "TMXLoader.h"

class Data;

class DataLoader : public TMXLoader
{
    public:
        DataLoader(XMLDocument* tmxFile, ErrorHandler* errorHandler):TMXLoader(tmxFile, errorHandler) {};

        friend class ImageLoader;
        friend class LayerLoader;

    private:
        bool loadDataNode(Data* data, XMLNode* dataNode);
        bool loadDataAttributes(Data* data, XMLElement* element);

};

#endif // DATALOADER_H
