#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <string>

class Property;
class Data;

using std::vector;
using std::string;

class Layer
{
    public:
        Layer(int tilesX, int tilesY);
        Layer();
        ~Layer();

        char type;

        string name;
        float opacity;
        bool visible;

        Data* layerData;

        int tilesX, tilesY;

        vector<Property*> properties;
};

#endif // LAYER_H
