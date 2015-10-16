#ifndef DATALOADER_H
#define DATALOADER_H

#include "TMXLoader.h"

#include <string>

class Data;

using std::string;

class DataLoader : public TMXLoader
{
    public:
        DataLoader(XMLDocument* tmxFile, Map* map, ErrorHandler* errorHandler):TMXLoader(tmxFile, map, errorHandler) {};

        friend class ImageLoader;
        friend class LayerLoader;

    private:
        bool loadDataNode(Data* data, XMLNode* dataNode);
        bool loadDataAttributes(Data* data, XMLElement* element);

        bool loadBase64_Uncompressed(string data);

        short* converCSVData(string data_string);

};

#endif // DATALOADER_H
