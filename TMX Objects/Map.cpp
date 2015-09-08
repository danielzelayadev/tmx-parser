#include "Map.h"

Map::Map(string path)
{
    this->path = path;
    version = 0;
    orientation = "";
    width = 0;
    height = 0;
    tilesX = 0;
    tilesY = 0;
    tileWidth = 0;
    tileHeight = 0;
    renderOrder = "";
}

Map::~Map()
{
   for(int i = 0; i < tilesets.size(); i++)
       delete tilesets.at(i);
    for(int i = 0; i < layers.size(); i++)
       delete layers.at(i);
    for(int i = 0; i < properties.size(); i++)
       delete properties.at(i);
}

Layer* Map::getLayer(string name)
{
   for(int i = 0; i < layers.size(); i++)
      if(!strcmp( layers[i]->name.c_str(), name.c_str() ))
         return layers[i];

   return nullptr;
}

Layer* Map::getLayer(int i)
{
    if(i >= 0 && i < layers.size())
      return layers[i];

    return nullptr;
}
