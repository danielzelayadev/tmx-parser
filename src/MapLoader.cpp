#include "MapLoader.h"

#include "Map.h"

bool MapLoader::loadMapAttributes(Map* tiledMap, XMLElement* element)
{
   if(!element) { errorHandler->setErrorId(MISSING_MAP_ATTRIBUTES); return false; }

   if(element->QueryFloatAttribute("version", &tiledMap->version) != 0) printf("No version attribute.\n");

   const char* ori = "";

   ori = element->Attribute("orientation");

   if(!ori) { ori = "Orthogonal"; } //DEFAULTING

   tiledMap->orientation = ori;

   element->QueryIntAttribute("width", &tiledMap->tilesX); //DEFAULTING

   element->QueryIntAttribute("height", &tiledMap->tilesY); //DEFAULTING

   element->QueryIntAttribute("tilewidth", &tiledMap->tileWidth); //DEFAULTING

   element->QueryIntAttribute("tileheight", &tiledMap->tileHeight); //DEFAULTING

   tiledMap->width = tiledMap->tilesX * tiledMap->tileWidth;
   tiledMap->height = tiledMap->tilesY * tiledMap->tileHeight;

   const char* ro = "";

   ro = element->Attribute("renderorder");

   if(ro) tiledMap->renderOrder = ro;

   return true;
}
