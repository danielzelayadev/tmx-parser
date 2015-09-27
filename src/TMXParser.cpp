#include "TMXParser.h"
#include "Data.h"

#include "Map.h"

#include <sstream>

using std::stringstream;

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

   MapLoader mapLoader(tmxFile);

   if(!mapLoader.loadMapAttributes(tiledMap, root->ToElement())) return nullptr;

   XMLNode* tmp = root->FirstChildElement();

   while(tmp)
   {

     if(!strcmp(tmp->Value(), "tileset"))
     {
       if(!loadTileSetNode(tiledMap, tmp)) return nullptr;
     }
     else if(!strcmp(tmp->Value(), "layer"))
     {
       if(!loadLayerNode(tiledMap, tmp)) return nullptr;
     }
     else if(!strcmp(tmp->Value(), "objectgroup"))
     {
       if(!loadObjectGroupNode(tiledMap, tmp)) return nullptr;
     }
     else if(!strcmp(tmp->Value(), "imagelayer"))
     {
       if(!loadImageLayerNode(tiledMap, tmp)) return nullptr;
     }
     else if(!strcmp(tmp->Value(), "properties"))
     {
        if(!loadProperties(&tiledMap->properties, tmp)) return nullptr;
     }
     tmp = tmp->NextSibling();
   }

   return tiledMap;
}

bool TMXParser::loadTileSetNode(Map* tiledMap, XMLNode* tilesetNode)
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
        if(!loadImageNode(image, tmp)) return false;
      }
      else if(!strcmp(tmp->Value(), "tile"))
      {
        Tile* tile;

        if(!tiledMap->tilesets.back()->tiles.size())
        { tile = new Tile(); tiledMap->tilesets.back()->tiles.push_back(tile); }

        else tile = tiledMap->tilesets.back()->tiles.back();

        if(!loadTileNode(tile, tmp)) return false;
      }
      else if(!strcmp(tmp->Value(), "terraintypes"))
      {
        if(!loadTerrainTypes(&tiledMap->tilesets.back()->terrainTypes, tmp)) return false;
      }
      else if(!strcmp(tmp->Value(), "properties"))
      {
        if(!loadProperties(&tiledMap->tilesets.back()->properties, tmp)) return false;
      }

      tmp = tmp->NextSibling();
   }

   return true;
}

 bool TMXParser::loadTileSetAttributes(Map* tiledMap, XMLElement* element)
 {
   if(!element) { errorHandler.setErrorId(MISSING_TILESET_ATTRIBUTES); return false; }

   Tileset* tileset = tiledMap->tilesets.at(tiledMap->tilesets.size()-1);

   if(element->QueryIntAttribute("firstgid", &tileset->firstgid) != 0)
   { errorHandler.setErrorId(NO_FIRSTGID_IN_TILESET); return false; }

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

 bool TMXParser::loadTileOffsetAttributes(Map* tiledMap, XMLElement* element)
 {
    Tileset* tileset = tiledMap->tilesets.at(tiledMap->tilesets.size()-1);

    element->QueryIntAttribute("x", &tileset->offset->x);
    element->QueryIntAttribute("y", &tileset->offset->y);

    return true;
 }

 bool TMXParser::loadImageNode(Image* image, XMLNode* imageNode)
 {
    if(!loadImageAttributes(image, imageNode->ToElement())) return false;

    XMLNode* tmp = imageNode->FirstChildElement();

    while(tmp)
    {

       if(!strcmp(tmp->Value(), "data"))
       {
          if(!loadDataNode(image->imageData, tmp)) return false;
       }

       tmp = tmp->NextSibling();
    }

    return true;
 }

 bool TMXParser::loadImageAttributes(Image* image, XMLElement* element)
 {
    if(!element) { errorHandler.setErrorId(MISSING_IMAGE_ATTRIBUTES); return false; }

    const char* str = "";

    str = element->Attribute("format");

    if(str) image->format = str;

    str = element->Attribute("source");

    if(!str) { errorHandler.setErrorId(NO_SOURCE_IN_IMAGE); return false; }

    image->source = str;

    str = element->Attribute("trans");

    if(str) image->trans = str;

    element->QueryIntAttribute("width", &image->width); //DEFAULTING

    element->QueryIntAttribute("height", &image->height); //DEFAULTING

    return true;
 }

 bool TMXParser::loadDataNode(Data* data, XMLNode* dataNode)
 {
    if(!loadDataAttributes(data, dataNode->ToElement())) return false;

    XMLNode* tmp = dataNode->FirstChildElement();

    while(tmp)
    {

      if(!strcmp(tmp->Value(), "tile"))
      {
         if(!loadTileNode(data->tile, tmp)) return false;
      }

      tmp = tmp->NextSibling();
    }

    return true;
 }

//Por ahora solo CSV
 bool TMXParser::loadDataAttributes(Data* data, XMLElement* element)
 {

   if(!element) { errorHandler.setErrorId(MISSING_DATA_ATTRIBUTES); return false; }

   const char* str = "";

   str = element->Attribute("encoding");

   if(!str) { errorHandler.setErrorId(NO_DATA_ENCODING_SPECIFIED); return false; }

   data->encoding = str;

   str = element->Attribute("compression");

   if(str) data->compression = str;

   if(!strcmp(data->encoding.c_str(), "csv"))
     data->data = element->GetText();

   else
   {
     errorHandler.setErrorId(UNSUPPORTED_DATA_ENCODING);
     return false;
   }

   return true;
 }

 bool TMXParser::loadTileNode(Tile* tile, XMLNode* tileNode)
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
        if(!loadProperties(&tile->properties, tmp)) return false;
     }

     tmp = tmp->NextSibling();
   }

   return true;
 }

  bool TMXParser::loadTileAttributes(Tile* tile, XMLElement* element)
  {
    if(!element) { errorHandler.setErrorId(MISSING_TILE_ATTRIBUTES); return false; }

    if(element->QueryIntAttribute("id", &tile->id) != 0)
    { errorHandler.setErrorId(NO_TILE_ID); return false; }

    const char* str = "";

    str = element->Attribute("terrain");

    if(str) tile->terrain = str;

    element->QueryFloatAttribute("probability", &tile->probability);

    return true;
  }

bool TMXParser::loadProperties(vector<Property*>* properties, XMLNode* propertiesNode)
{
    XMLNode* tmp = propertiesNode->FirstChildElement();

    while(tmp)
    {

       if(!strcmp(tmp->Value(), "property"))
       {
          if(!loadPropertyAttributes(properties, tmp->ToElement())) return false;
       }

       tmp = tmp->NextSibling();
    }

    return true;
}

bool TMXParser::loadPropertyAttributes(vector<Property*>* properties, XMLElement* element)
{
    if(!element) { errorHandler.setErrorId(MISSING_PROPERTY_ATTRIBUTES); return false; }

    Property* prop = new Property();

    const char* str = "";

    str = element->Attribute("name");

    if(str) prop->name = str;

    str = element->Attribute("value");

    if(str) prop->value = str;

    properties->push_back(prop);

    return true;
}

bool TMXParser::loadTerrainTypes(vector<Terrain*>* terrains, XMLNode* terraintypeNode)
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

bool TMXParser::loadTerrainAttributes(vector<Terrain*>* terrains, XMLElement* element)
{
    if(!element) { errorHandler.setErrorId(MISSING_TERRAIN_ATTRIBUTES); return false; }

    Terrain* terrain = new Terrain();

    const char* str = element->Attribute("name");

    if(!str) { errorHandler.setErrorId(NO_NAME_IN_TERRAIN); return false; }

    terrain->name = str;

    if(element->QueryIntAttribute("tile", &terrain->tile) != 0)
    { errorHandler.setErrorId(NO_TILE_IN_TERRAIN); return false; }

    terrains->push_back(terrain);

    return true;
}

bool TMXParser::loadLayerNode(Map* tiledMap, XMLNode* layerNode)
{
    Layer* layer = new Layer(tiledMap->width, tiledMap->height);

    if(!loadLayerAttributes(layer, layerNode->ToElement())) { delete layer; return false; }

    XMLNode* tmp = layerNode->FirstChildElement();

    while(tmp)
    {

       if(!strcmp(tmp->Value(), "data"))
       {
          if(!loadDataNode(layer->layerData, tmp)) return false;

          layer->convertData();
       }

       else if(!strcmp(tmp->Value(), "properties"))
       {
         if(!loadProperties(&layer->properties, tmp)) return false;
       }

       tmp = tmp->NextSibling();
    }

    tiledMap->layers.push_back(layer);

    return true;
}

bool TMXParser::loadLayerAttributes(Layer* layer, XMLElement* element)
{
    if(!element) { errorHandler.setErrorId(MISSING_LAYER_ATTRIBUTES); return false; }

    const char* str = element->Attribute("name");

    if(!str) { errorHandler.setErrorId(NO_NAME_IN_LAYER); return false; }

    layer->name = str;

    element->QueryFloatAttribute("opacity", &layer->opacity);

    element->QueryBoolAttribute("visible", &layer->visible);

    return true;
}

bool TMXParser::loadImageLayerNode(Map* tiledMap, XMLNode* imageLayerNode)
{
    ImageLayer* iLayer = new ImageLayer();

    if(!loadImageLayerAttributes(iLayer, imageLayerNode->ToElement())) { delete iLayer; return false; }

    XMLNode* tmp = imageLayerNode->FirstChildElement();

    while(tmp)
    {

      if(!strcmp(tmp->Value(), "properties"))
      {
         if(!loadProperties(&iLayer->properties, tmp)) return false;
      }
      else if(!strcmp(tmp->Value(), "image"))
      {
         if(!loadImageNode(iLayer->image, tmp)) return false;
      }

      tmp = tmp->NextSibling();
    }

    tiledMap->layers.push_back(iLayer);

    return true;
}

bool TMXParser::loadImageLayerAttributes(ImageLayer* iLayer, XMLElement* element)
{
    if(!loadLayerAttributes((Layer*)iLayer, element)) return false;

    element->QueryIntAttribute("x", &iLayer->x);

    element->QueryIntAttribute("y", &iLayer->y);

    return true;
}

bool TMXParser::loadObjectGroupNode(Map* tiledMap, XMLNode* objectGroupNode)
{
    ObjectLayer* oLayer = new ObjectLayer();

    if(!loadObjectLayerAttributes(oLayer, objectGroupNode->ToElement())) return false;

    XMLNode* tmp = objectGroupNode->FirstChildElement();

    while(tmp)
    {

      if(!strcmp(tmp->Value(), "object"))
      {
         if(!loadObject(&oLayer->objects, tmp)) return false;
      }

      else if(!strcmp(tmp->Value(), "properties"))
      {
        if(!loadProperties(&oLayer->properties, tmp)) return false;
      }

      tmp = tmp->NextSibling();
    }

    tiledMap->layers.push_back(oLayer);

    return true;
}

bool TMXParser::loadObjectLayerAttributes(ObjectLayer* oLayer, XMLElement* element)
{
    return loadLayerAttributes((Layer*)oLayer, element);
}

bool TMXParser::loadObject(vector<MapObject*>* objects, XMLNode* objectNode)
{
    MapObject object;

    if(!loadObjectAttributes(&object, objectNode->ToElement())) return false;

    XMLNode* tmp = objectNode->FirstChildElement(),
             *cache = nullptr;
    bool isRect = false, isEllipse = false, isPolygon = false, isPolyline = false;

    while(tmp)
    {

      if(!strcmp(tmp->Value(), "properties"))
      {
         if(!loadProperties(&object.properties, tmp)) return false;
      }

      else if(!strcmp(tmp->Value(), "image"))
      {
         object.image = new Image();
         if(!loadImageNode(object.image, tmp)) return false;
      }

      else if(!strcmp(tmp->Value(), "ellipse"))
      {
         isEllipse = true;
      }

      else if(!strcmp(tmp->Value(), "polygon"))
      {
         isPolygon = true;
         cache = tmp;
      }

      else if(!strcmp(tmp->Value(), "polyline"))
      {
         isPolyline = true;
         cache = tmp;
      }

      tmp = tmp->NextSibling();
    }

    isRect = !isEllipse && !isPolygon && !isPolyline;

    MapObject* newObject;

    if(isRect)
    { newObject = new RectangleMapObject(); loadRectAttributes((RectangleMapObject*)newObject, objectNode->ToElement()); }
    else if(isEllipse)
    { newObject = new EllipseMapObject(); loadEllipseAttributes((EllipseMapObject*)newObject, objectNode->ToElement()); }
    else if(isPolygon)
    { newObject = new PolygonMapObject(); loadPolygonAttributes((PolygonMapObject*)newObject, cache->ToElement()); }
    else if(isPolyline)
    { newObject = new PolylineMapObject(); loadPolylineAttributes((PolylineMapObject*)newObject, cache->ToElement()); }

    newObject->copyObj(&object);

    objects->push_back(newObject);

    return true;
}

bool TMXParser::loadObjectAttributes(MapObject* object, XMLElement* element)
{
    if(!element) { errorHandler.setErrorId(MISSING_OBJECT_ATTRIBUTES); return false; }

    element->QueryIntAttribute("id", &object->id);

    element->QueryIntAttribute("gid", &object->gid);

    element->QueryIntAttribute("rotation", &object->rotation);

    element->QueryBoolAttribute("visible", &object->visible);

    const char* str = "";

    str = element->Attribute("name");

    if(str) object->name = str;

    str = element->Attribute("type");

    if(str) object->type = str;

    return true;
}

bool TMXParser::loadRectAttributes(RectangleMapObject* rmo, XMLElement* element)
{
    if(!element) { errorHandler.setErrorId(MISSING_OBJECT_ATTRIBUTES); return false; }

    element->QueryIntAttribute("x", &rmo->x);

    element->QueryIntAttribute("y", &rmo->y);

    element->QueryIntAttribute("width", &rmo->width);

    element->QueryIntAttribute("height", &rmo->height);

    return true;
}

bool TMXParser::loadEllipseAttributes(EllipseMapObject* ellipse, XMLElement* element)
{
    if(!element) { errorHandler.setErrorId(MISSING_OBJECT_ATTRIBUTES); return false; }

    element->QueryIntAttribute("x", &ellipse->x);

    element->QueryIntAttribute("y", &ellipse->y);

    element->QueryIntAttribute("width", &ellipse->width);

    element->QueryIntAttribute("height", &ellipse->height);

    return true;
}

bool TMXParser::loadPolygonAttributes(PolygonMapObject* poly, XMLElement* element)
{
    if(!element) { errorHandler.setErrorId(MISSING_OBJECT_ATTRIBUTES);return false; }

    const char* str = "";

    str = element->Attribute("points");

    if(str)
    {
       string points = str;
       stringstream strm;

       for(int i = 0; i < points.size(); i++)
       {
          char c = points.at(i);

          if(c == ',')
          {
             int xPos = 0;
             strm >> xPos;
             strm.str(string());
             poly->x.push_back(xPos);
          }
          else if(c == ' ')
          {
             int yPos = 0;
             strm >> yPos;
             strm.str(string());
             poly->y.push_back(yPos);
          }
          else
             strm << c;
       }

    }

    return true;
}

bool TMXParser::loadPolylineAttributes(PolylineMapObject* poly, XMLElement* element)
{
    if(!element) { errorHandler.setErrorId(MISSING_OBJECT_ATTRIBUTES); return false; }

    const char* str = "";

    str = element->Attribute("points");

    if(str)
    {
       string points = str;
       stringstream strm;

       for(int i = 0; i < points.size(); i++)
       {
          char c = points.at(i);

          if(c == ',')
          {
             int xPos = 0;
             strm >> xPos;
             strm.clear();
             poly->x.push_back(xPos);
          }
          else if(c == ' ')
          {
             int yPos = 0;
             strm >> yPos;
             strm.clear();
             poly->y.push_back(yPos);
          }
          else
             strm << c;

       }

    }

    return true;
}
