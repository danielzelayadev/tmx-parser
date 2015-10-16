#include "TMXParser.h"

#include "Map.h"
#include "MapLoader.h"

#include "TilesetLoader.h"
#include "LayerLoader.h"
#include "PropertyLoader.h"

TMXParser::TMXParser()
{
   fileDir = "";
   tmxFile = nullptr;
}

TMXParser::TMXParser(string fileDir)
{
   this->fileDir = fileDir;
   tmxFile = new XMLDocument();
}

TMXParser::~TMXParser()
{
   if(tmxFile) delete tmxFile;
}

char* TMXParser::getError()
{
   return errorHandler.getError();
}

Map* TMXParser::parse(string fileDir)
{
   this->fileDir = fileDir;

   if(tmxFile) delete tmxFile;

   tmxFile = new XMLDocument();

   return parse();
}

Map* TMXParser::parse()
{
   if(fileDir.size() < 5 || fileDir.substr(fileDir.size()-4, 4) != ".tmx")
   { errorHandler.setErrorId(WRONG_EXTENSION); return nullptr;}

   if(tmxFile->LoadFile(fileDir.c_str()) != 0) { errorHandler.setErrorId(FILE_DOES_NOT_EXIST); return nullptr; }

   string path = "";
   int found = fileDir.find_last_of("/");
   if(found != fileDir.size()) path = fileDir.substr(0, found);

   Map* tiledMap = new Map(path);

   XMLNode* root = tmxFile->FirstChildElement();

   if(!root) { errorHandler.setErrorId(NO_MAP_NODE); return nullptr; }

   MapLoader mapLoader(tmxFile, tiledMap, &errorHandler);

   if(!mapLoader.loadMapAttributes(tiledMap, root->ToElement())) return nullptr;

   XMLNode* tmp = root->FirstChildElement();

   while(tmp)
   {

     if(!strcmp(tmp->Value(), "tileset"))
     {
       TilesetLoader tilesetLoader(tmxFile, tiledMap, &errorHandler);
       if(!tilesetLoader.loadTileSetNode(tiledMap, tmp)) return nullptr;
     }
     else if(!strcmp(tmp->Value(), "layer"))
     {
       LayerLoader layerLoader(tmxFile, tiledMap, &errorHandler);
       if(!layerLoader.loadLayerNode(tiledMap, tmp)) return nullptr;
     }
     else if(!strcmp(tmp->Value(), "objectgroup"))
     {
       LayerLoader layerLoader(tmxFile, tiledMap, &errorHandler);
       if(!layerLoader.loadObjectGroupNode(tiledMap, tmp)) return nullptr;
     }
     else if(!strcmp(tmp->Value(), "imagelayer"))
     {
        LayerLoader layerLoader(tmxFile, tiledMap, &errorHandler);
       if(!layerLoader.loadImageLayerNode(tiledMap, tmp)) return nullptr;
     }
     else if(!strcmp(tmp->Value(), "properties"))
     {
        PropertyLoader propertyLoader(tmxFile, tiledMap, &errorHandler);
        if(!propertyLoader.loadProperties(&tiledMap->properties, tmp)) return nullptr;
     }
     tmp = tmp->NextSibling();
   }

   return tiledMap;
}
