#ifndef DATA_H
#define DATA_H

#include <string>

class Tile;

class Data
{
    public:
        Data();
        ~Data();

        std::string encoding;
        std::string compression;
        short* data;

        Tile* tile;
};

#endif // DATA_H
