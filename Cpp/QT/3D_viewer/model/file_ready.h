#include "file_parser.h"
#include <iostream>

class FileReady {

public:
    minmax reading(QString str, QVector<QVector<float>>& vertices, QVector<QVector<int>>& edges, QVector<float>& flatVertices);
    
    minmax mxy;  // структура где хранится Макс и Мин по оси X и Y
    FileParser fp;
};