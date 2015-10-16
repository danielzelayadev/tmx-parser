#include "Data.h"
#include "Tile.h"

Data::Data()
{
    this->compression = "";
    this->encoding = "";
    this->data = nullptr;
    this->tile = new Tile();
}

Data::~Data()
{
   delete tile;
}
