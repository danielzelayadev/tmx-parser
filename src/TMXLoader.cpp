#include "TMXLoader.h"

TMXLoader::TMXLoader(XMLDocument* tmxFile, ErrorHandler* errorHandler)
{
   this->tmxFile = tmxFile;
   this->errorHandler = errorHandler;
}
