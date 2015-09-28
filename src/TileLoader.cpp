#include "TileLoader.h"

#include "PropertyLoader.h"

#include "Tile.h"

bool TileLoader::loadTileNode(Tile* tile, XMLNode* tileNode)
 {
   if(!loadTileAttributes(tile, tileNode->ToElement())) return false;

   XMLNode* tmp = tileNode->FirstChildElement();

   while(tmp)
   {

     if(!strcmp(tmp->Value(), "objectgroup"))
     {

     }

     else if(!strcmp(tmp->Value(), "properties"))
     {
        PropertyLoader propertyLoader(tmxFile, errorHandler);
        if(!propertyLoader.loadProperties(&tile->properties, tmp)) return false;
     }

     tmp = tmp->NextSibling();
   }

   return true;
 }

  bool TileLoader::loadTileAttributes(Tile* tile, XMLElement* element)
  {
    if(!element) { errorHandler->setErrorId(MISSING_TILE_ATTRIBUTES); return false; }

    if(element->QueryIntAttribute("id", &tile->id) != 0)
    { errorHandler->setErrorId(NO_TILE_ID); return false; }

    const char* str = "";

    str = element->Attribute("terrain");

    if(str) tile->terrain = str;

    element->QueryFloatAttribute("probability", &tile->probability);

    return true;
  }
