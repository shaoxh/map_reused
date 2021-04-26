//
// Created by godu on 2021/4/25.
//

#ifndef MAP_REUSED_MAPLOAD_H
#define MAP_REUSED_MAPLOAD_H

#include <fstream>
#include "opencv2/highgui/highgui.hpp"
#include "Converter.h"
#include "iostream"

using namespace std;

class MapLoad{
public:
    bool LoadKeyFrame(ifstream &f);
    bool LoadMappoint(ifstream &f);
};

#endif //MAP_REUSED_MAPLOAD_H
