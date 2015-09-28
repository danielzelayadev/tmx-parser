#include "DataLoader.h"

#include "Data.h"

#include "TileLoader.h"

bool DataLoader::loadDataNode(Data* data, XMLNode* dataNode)
 {
    if(!loadDataAttributes(data, dataNode->ToElement())) return false;

    XMLNode* tmp = dataNode->FirstChildElement();

    while(tmp)
    {

      if(!strcmp(tmp->Value(), "tile"))
      {
         TileLoader tileLoader(tmxFile, errorHandler);
         if(!tileLoader.loadTileNode(data->tile, tmp)) return false;
      }

      tmp = tmp->NextSibling();
    }

    return true;
 }

//Por ahora solo CSV
 bool DataLoader::loadDataAttributes(Data* data, XMLElement* element)
 {

   if(!element) { errorHandler->setErrorId(MISSING_DATA_ATTRIBUTES); return false; }

   const char* str = "";

   str = element->Attribute("encoding");

   if(!str) { errorHandler->setErrorId(NO_DATA_ENCODING_SPECIFIED); return false; }

   data->encoding = str;

   str = element->Attribute("compression");

   if(str) data->compression = str;

   if(!strcmp(data->encoding.c_str(), "csv"))
     data->data = element->GetText();

   else
   {
     errorHandler->setErrorId(UNSUPPORTED_DATA_ENCODING);
     return false;
   }

   return true;
 }
