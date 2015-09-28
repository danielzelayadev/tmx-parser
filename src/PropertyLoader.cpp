#include "PropertyLoader.h"

#include "Property.h"

bool PropertyLoader::loadProperties(vector<Property*>* properties, XMLNode* propertiesNode)
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

bool PropertyLoader::loadPropertyAttributes(vector<Property*>* properties, XMLElement* element)
{
    if(!element) { errorHandler->setErrorId(MISSING_PROPERTY_ATTRIBUTES); return false; }

    Property* prop = new Property();

    const char* str = "";

    str = element->Attribute("name");

    if(str) prop->name = str;

    str = element->Attribute("value");

    if(str) prop->value = str;

    properties->push_back(prop);

    return true;
}
