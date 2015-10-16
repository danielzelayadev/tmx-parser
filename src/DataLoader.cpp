#include "DataLoader.h"

#include "Data.h"

#include "TileLoader.h"

#include "Map.h"

#include <sstream>

using std::stringstream;

bool DataLoader::loadDataNode(Data* data, XMLNode* dataNode)
 {
    if(!loadDataAttributes(data, dataNode->ToElement())) return false;

    XMLNode* tmp = dataNode->FirstChildElement();

    while(tmp)
    {

      if(!strcmp(tmp->Value(), "tile"))
      {
         TileLoader tileLoader(tmxFile, map, errorHandler);
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
     data->data = converCSVData(element->GetText());

   else
   {
     errorHandler->setErrorId(UNSUPPORTED_DATA_ENCODING);
     return false;
   }

   return true;
 }

 short* DataLoader::converCSVData(string data_string)
 {
   string tmp = data_string;

   short* data = new short[map->getTilesX()*map->getTilesY()];

   int dCtr = 0;

   while(true)
   {
      string valStr("");
      stringstream strm;

      if(tmp.find(",") == tmp.npos)
      {
        valStr = tmp.substr(0, tmp.size()-1);
        strm << valStr;
        strm >> data[dCtr];
        break;
      }

      int firstCommaIndex = tmp.find_first_of(",");

      valStr = tmp.substr(0, firstCommaIndex);
      strm << valStr;
      strm >> data[dCtr];

      dCtr++;
      tmp = tmp.substr(firstCommaIndex+1, tmp.size()-firstCommaIndex+1);
   }

    return data;
 }

bool DataLoader::loadBase64_Uncompressed(string data)
{

}
