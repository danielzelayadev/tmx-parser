#include "ErrorHandler.h"

ErrorHandler::ErrorHandler()
{
    errId = -1;
}

void ErrorHandler::setErrorId(int id)
{
   this->errId = id;
}

char* ErrorHandler::getError()
{
    switch(errId)
    {
        case FILE_DOES_NOT_EXIST:
        return "The file directory submitted does not exist.\n";

        case WRONG_EXTENSION:
        return "This is not a TMX file. Make sure the file extension is .tmx.\n";

        case NO_MAP_NODE:
        return "The TMX file has no map node.\n";

        case MISSING_MAP_ATTRIBUTES:
        return "Required attributes from the map node are missing.\n";

        case MISSING_TILESET_ATTRIBUTES:
        return "Required attributes from a certain tileset node are missing.\n";

        case NO_FIRSTGID_IN_TILESET:
        return "No firstgid specified on a tileset node.\n";

        case MISSING_IMAGE_ATTRIBUTES:
        return "Required attributes from a certain image node are missing.\n";

        case NO_SOURCE_IN_IMAGE:
        return "No source directory for an image node.\n";

        case MISSING_DATA_ATTRIBUTES:
        return "Required attributes from a certain data node are missing.\n";

        case NO_DATA_ENCODING_SPECIFIED:
        return "No data encoding specified on layer data.\n";

        case UNSUPPORTED_DATA_ENCODING:
        return "The encoding specified for a layer's data is currently unsupported by the parser.\n";

        case MISSING_TILE_ATTRIBUTES:
        return "Required attributes from a certain tile node are missing.\n";

        case NO_TILE_ID:
        return "No tile id specified for a certain tile node.\n";

        case MISSING_PROPERTY_ATTRIBUTES:
        return "Required attributes from a certain property node are missing.\n";

        case MISSING_TERRAIN_ATTRIBUTES:
        return "Required attributes from a certain terrain node are missing.\n";

        case NO_NAME_IN_TERRAIN:
        return "No terrain name specified.\n";

        case NO_TILE_IN_TERRAIN:
        return "No tile specified for a certain terrain node.\n";

        case MISSING_LAYER_ATTRIBUTES:
        return "Required attributes from a certain layer node are missing.\n";

        case NO_NAME_IN_LAYER:
        return "No layer name specified for a certain layer node.\n";

        case MISSING_IMAGE_LAYER_ATTRIBUTES:
        return "Required attributes from a certain image layer node are missing.\n";

        case MISSING_OBJECT_ATTRIBUTES:
        return "Required attributes from a certain object node are missing.\n";

        default:
        return "No known error detected.\n";
    }
}
