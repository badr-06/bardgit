#pragma once

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QString>
#include <QtCore/QVector>
#include <cfloat>

struct minmax{
    float maxX = FLT_MIN;
    float minX = FLT_MAX;

    float maxY = FLT_MIN;
    float minY = FLT_MAX;

    float maxZ = FLT_MIN;
    float minZ = FLT_MAX;
};

minmax file_parser(QString str, QVector<QVector<float>>& vertices, QVector<QVector<int>>& edges);
void MinMaxFuncion(minmax& mxy, const QVector<float>& v);
