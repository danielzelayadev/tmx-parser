#include "LayerLoader.h"

#include "Map.h"
#include "DataLoader.h"
#include "PropertyLoader.h"
#include "ImageLoader.h"
#include "ImageLayer.h"
#include "ObjectLayer.h"
#include "ObjectLoader.h"

bool LayerLoader::loadLayerNode(Map* tiledMap, XMLNode* layerNode)
{
    Layer* layer = new Layer(tiledMap->width, tiledMap->height);

    if(!loadLayerAttributes(layer, layerNode->ToElement())) { delete layer; return false; }

    XMLNode* tmp = layerNode->FirstChildElement();

    while(tmp)
    {

       if(!strcmp(tmp->Value(), "data"))
       {
          DataLoader dataLoader(tmxFile, errorHandler);
          if(!dataLoader.loadDataNode(layer->layerData, tmp)) return false;

          layer->convertData();
       }

       else if(!strcmp(tmp->Value(), "properties"))
       {
         PropertyLoader propertyLoader(tmxFile, errorHandler);
         if(!propertyLoader.loadProperties(&layer->properties, tmp)) return false;
       }

       tmp = tmp->NextSibling();
    }

    tiledMap->layers.push_back(layer);

    return true;
}

bool LayerLoader::loadLayerAttributes(Layer* layer, XMLElement* element)
{
    if(!element) { errorHandler->setErrorId(MISSING_LAYER_ATTRIBUTES); return false; }

    const char* str = element->Attribute("name");

    if(!str) { errorHandler->setErrorId(NO_NAME_IN_LAYER); return false; }

    layer->name = str;

    element->QueryFloatAttribute("opacity", &layer->opacity);

    element->QueryBoolAttribute("visible", &layer->visible);

    return true;
}

bool LayerLoader::loadImageLayerNode(Map* tiledMap, XMLNode* imageLayerNode)
{
    ImageLayer* iLayer = new ImageLayer();

    if(!loadImageLayerAttributes(iLayer, imageLayerNode->ToElement())) { delete iLayer; return false; }

    XMLNode* tmp = imageLayerNode->FirstChildElement();

    while(tmp)
    {

      if(!strcmp(tmp->Value(), "properties"))
      {
         PropertyLoader propertyLoader(tmxFile, errorHandler);
         if(!propertyLoader.loadProperties(&iLayer->properties, tmp)) return false;
      }
      else if(!strcmp(tmp->Value(), "image"))
      {
         ImageLoader imageLoader(tmxFile, errorHandler);
         if(!imageLoader.loadImageNode(iLayer->image, tmp)) return false;
      }

      tmp = tmp->NextSibling();
    }

    tiledMap->layers.push_back(iLayer);

    return true;
}

bool LayerLoader::loadImageLayerAttributes(ImageLayer* iLayer, XMLElement* element)
{
    if(!loadLayerAttributes((Layer*)iLayer, element)) return false;

    element->QueryIntAttribute("x", &iLayer->x);

    element->QueryIntAttribute("y", &iLayer->y);

    return true;
}

bool LayerLoader::loadObjectGroupNode(Map* tiledMap, XMLNode* objectGroupNode)
{
    ObjectLayer* oLayer = new ObjectLayer();

    if(!loadObjectLayerAttributes(oLayer, objectGroupNode->ToElement())) return false;

    XMLNode* tmp = objectGroupNode->FirstChildElement();

    while(tmp)
    {

      if(!strcmp(tmp->Value(), "object"))
      {
         ObjectLoader objectLoader(tmxFile, errorHandler);
         if(!objectLoader.loadObject(&oLayer->objects, tmp)) return false;
      }

      else if(!strcmp(tmp->Value(), "properties"))
      {
        PropertyLoader propertyLoader(tmxFile, errorHandler);
        if(!propertyLoader.loadProperties(&oLayer->properties, tmp)) return false;
      }

      tmp = tmp->NextSibling();
    }

    tiledMap->layers.push_back(oLayer);

    return true;
}

bool LayerLoader::loadObjectLayerAttributes(ObjectLayer* oLayer, XMLElement* element)
{
    return loadLayerAttributes((Layer*)oLayer, element);
}
