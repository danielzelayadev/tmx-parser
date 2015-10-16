#include "ImageLoader.h"

#include "Image.h"

#include "DataLoader.h"

bool ImageLoader::loadImageNode(Image* image, XMLNode* imageNode)
 {
    if(!loadImageAttributes(image, imageNode->ToElement())) return false;

    XMLNode* tmp = imageNode->FirstChildElement();

    while(tmp)
    {

       if(!strcmp(tmp->Value(), "data"))
       {
          DataLoader dataLoader(tmxFile, map, errorHandler);
          if(!dataLoader.loadDataNode(image->imageData, tmp)) return false;
       }

       tmp = tmp->NextSibling();
    }

    return true;
 }

 bool ImageLoader::loadImageAttributes(Image* image, XMLElement* element)
 {
    if(!element) { errorHandler->setErrorId(MISSING_IMAGE_ATTRIBUTES); return false; }

    const char* str = "";

    str = element->Attribute("format");

    if(str) image->format = str;

    str = element->Attribute("source");

    if(!str) { errorHandler->setErrorId(NO_SOURCE_IN_IMAGE); return false; }

    image->source = str;

    str = element->Attribute("trans");

    if(str) image->trans = str;

    element->QueryIntAttribute("width", &image->width); //DEFAULTING

    element->QueryIntAttribute("height", &image->height); //DEFAULTING

    return true;
 }
