#pragma once

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QString>
#include <QtCore/QVector>
#include "../info.h"

class FileParser {
    void MinMaxFuncion(minmax& mxy, const QVector<float>& v);
    int face_extract(QString str);

public:
    FileParser() {};
    ~FileParser() {};

    void file_parser(QFile& file, minmax& mxy, QVector<QVector<float>>& vertices, QVector<QVector<int>>& edges, QVector<float>& flatVertices);
    void checkQvectors(QVector<QVector<float>>& vertices, QVector<QVector<int>>& edges, QVector<float>& flatVertices);
};