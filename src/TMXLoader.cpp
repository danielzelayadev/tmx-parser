#include "TMXLoader.h"

TMXLoader::TMXLoader(XMLDocument* tmxFile, Map* map, ErrorHandler* errorHandler)
{
   this->tmxFile = tmxFile;
   this->map = map;
   this->errorHandler = errorHandler;
}
