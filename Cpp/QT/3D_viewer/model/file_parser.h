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

    minmax file_parser(QString str, QVector<QVector<float>>& vertices, QVector<QVector<int>>& edges);

};