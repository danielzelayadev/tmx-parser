#include "TilesetLoader.h"

#include "Map.h"

#include "ImageLoader.h"
#include "TileLoader.h"
#include "PropertyLoader.h"
#include "TerrainLoader.h"

bool TilesetLoader::loadTileSetNode(Map* tiledMap, XMLNode* tilesetNode)
{
   tiledMap->tilesets.push_back(new Tileset());

   if(!loadTileSetAttributes(tiledMap, tilesetNode->ToElement())) return false;

   XMLNode* tmp = tilesetNode->FirstChildElement();

   while(tmp)
   {

      if(!strcmp(tmp->Value(), "tileoffset"))
      {
         if(!loadTileOffsetAttributes(tiledMap, tilesetNode->ToElement())) return false;
      }
      else if(!strcmp(tmp->Value(), "image"))
      {
        Image* image = tiledMap->tilesets.back()->image;
        ImageLoader imageLoader(tmxFile, errorHandler);
        if(!imageLoader.loadImageNode(image, tmp)) return false;
      }
      else if(!strcmp(tmp->Value(), "tile"))
      {
        Tile* tile;

        if(!tiledMap->tilesets.back()->tiles.size())
        { tile = new Tile(); tiledMap->tilesets.back()->tiles.push_back(tile); }

        else tile = tiledMap->tilesets.back()->tiles.back();

        TileLoader tileLoader(tmxFile, errorHandler);
        if(!tileLoader.loadTileNode(tile, tmp)) return false;
      }
      else if(!strcmp(tmp->Value(), "terraintypes"))
      {
        TerrainLoader terrainLoader(tmxFile, errorHandler);
        if(!terrainLoader.loadTerrainTypes(&tiledMap->tilesets.back()->terrainTypes, tmp)) return false;
      }
      else if(!strcmp(tmp->Value(), "properties"))
      {
        PropertyLoader propertyLoader(tmxFile, errorHandler);
        if(!propertyLoader.loadProperties(&tiledMap->tilesets.back()->properties, tmp)) return false;
      }

      tmp = tmp->NextSibling();
   }

   return true;
}

 bool TilesetLoader::loadTileSetAttributes(Map* tiledMap, XMLElement* element)
 {
   if(!element) { errorHandler->setErrorId(MISSING_TILESET_ATTRIBUTES); return false; }

   Tileset* tileset = tiledMap->tilesets.at(tiledMap->tilesets.size()-1);

   if(element->QueryIntAttribute("firstgid", &tileset->firstgid) != 0)
   { errorHandler->setErrorId(NO_FIRSTGID_IN_TILESET); return false; }

   const char* src = "";

   src = element->Attribute("source");

   if(src) tileset->source = src;

   const char* nm = "";

   nm = element->Attribute("name");

   if(nm) tileset->name = nm;

   element->QueryIntAttribute("tilewidth", &tileset->tilewidth);

   element->QueryIntAttribute("tileheight", &tileset->tileheight);

   element->QueryIntAttribute("spacing", &tileset->spacing);

   element->QueryIntAttribute("margin", &tileset->margin);

   return true;
 }

 bool TilesetLoader::loadTileOffsetAttributes(Map* tiledMap, XMLElement* element)
 {
    Tileset* tileset = tiledMap->tilesets.at(tiledMap->tilesets.size()-1);

    element->QueryIntAttribute("x", &tileset->offset->x);
    element->QueryIntAttribute("y", &tileset->offset->y);

    return true;
 }
