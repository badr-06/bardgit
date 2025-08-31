#pragma once

#include <cfloat>

struct minmax{
    float maxX = FLT_MIN;
    float minX = FLT_MAX;

    float maxY = FLT_MIN;
    float minY = FLT_MAX;

    float maxZ = FLT_MIN;
    float minZ = FLT_MAX;
};