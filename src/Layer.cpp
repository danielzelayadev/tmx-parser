#include "Layer.h"
#include "Data.h"

#include <sstream>
#include <stdio.h>
#include <iostream>

using namespace std;

Layer::Layer()
{
  this->type = 'L';
  this->name = "";
  this->opacity = 1.0;
  this->visible = true;
  this->layerData = new Data();
}

Layer::Layer(int tilesX, int tilesY)
{
  this->tilesX = tilesX;
  this->tilesY = tilesY;
  this->type = 'L';
  this->name = "";
  this->opacity = 1.0;
  this->visible = true;
  this->layerData = new Data();
}

Layer::~Layer()
{
    delete layerData;

    for(int i = 0; i < properties.size(); i++)
       delete properties[i];
}
