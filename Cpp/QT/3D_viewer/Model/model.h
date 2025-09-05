#pragma once

#include <QVector3D>
#include "../info.h"

class Model{

public:
    void calculateCenter(minmax& mxy, QVector3D& modelC);
    float calculateRadius(minmax& mxy);
    
};