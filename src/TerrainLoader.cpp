#include "TerrainLoader.h"

#include "Terrain.h"

bool TerrainLoader::loadTerrainTypes(vector<Terrain*>* terrains, XMLNode* terraintypeNode)
{
    XMLNode* tmp = terraintypeNode->FirstChildElement();

    while(tmp)
    {

      if(!strcmp(tmp->Value(), "terrain"))
      {
        if(!loadTerrainAttributes(terrains, tmp->ToElement())) return false;
      }

      tmp = tmp->NextSibling();
    }

    return true;
}

bool TerrainLoader::loadTerrainAttributes(vector<Terrain*>* terrains, XMLElement* element)
{
    if(!element) { errorHandler->setErrorId(MISSING_TERRAIN_ATTRIBUTES); return false; }

    Terrain* terrain = new Terrain();

    const char* str = element->Attribute("name");

    if(!str) { errorHandler->setErrorId(NO_NAME_IN_TERRAIN); return false; }

    terrain->name = str;

    if(element->QueryIntAttribute("tile", &terrain->tile) != 0)
    { errorHandler->setErrorId(NO_TILE_IN_TERRAIN); return false; }

    terrains->push_back(terrain);

    return true;
}
