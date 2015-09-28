#include "ObjectLoader.h"

#include <sstream>

using std::stringstream;

#include "MapObject.h"
#include "RectangleMapObject.h"
#include "EllipseMapObject.h"
#include "PolygonMapObject.h"
#include "PolylineMapObject.h"

#include "PropertyLoader.h"
#include "ImageLoader.h"

bool ObjectLoader::loadObject(vector<MapObject*>* objects, XMLNode* objectNode)
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
         PropertyLoader propertyLoader(tmxFile, errorHandler);
         if(!propertyLoader.loadProperties(&object.properties, tmp)) return false;
      }

      else if(!strcmp(tmp->Value(), "image"))
      {
         object.image = new Image();
         ImageLoader imageLoader(tmxFile, errorHandler);
         if(!imageLoader.loadImageNode(object.image, tmp)) return false;
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

bool ObjectLoader::loadObjectAttributes(MapObject* object, XMLElement* element)
{
    if(!element) { errorHandler->setErrorId(MISSING_OBJECT_ATTRIBUTES); return false; }

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

bool ObjectLoader::loadRectAttributes(RectangleMapObject* rmo, XMLElement* element)
{
    if(!element) { errorHandler->setErrorId(MISSING_OBJECT_ATTRIBUTES); return false; }

    element->QueryIntAttribute("x", &rmo->x);

    element->QueryIntAttribute("y", &rmo->y);

    element->QueryIntAttribute("width", &rmo->width);

    element->QueryIntAttribute("height", &rmo->height);

    return true;
}

bool ObjectLoader::loadEllipseAttributes(EllipseMapObject* ellipse, XMLElement* element)
{
    if(!element) { errorHandler->setErrorId(MISSING_OBJECT_ATTRIBUTES); return false; }

    element->QueryIntAttribute("x", &ellipse->x);

    element->QueryIntAttribute("y", &ellipse->y);

    element->QueryIntAttribute("width", &ellipse->width);

    element->QueryIntAttribute("height", &ellipse->height);

    return true;
}

bool ObjectLoader::loadPolygonAttributes(PolygonMapObject* poly, XMLElement* element)
{
    if(!element) { errorHandler->setErrorId(MISSING_OBJECT_ATTRIBUTES);return false; }

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

bool ObjectLoader::loadPolylineAttributes(PolylineMapObject* poly, XMLElement* element)
{
    if(!element) { errorHandler->setErrorId(MISSING_OBJECT_ATTRIBUTES); return false; }

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
