#include "controller.h"

minmax Controller::LoadVertics(QString nameFile, QVector<QVector<float>> &vertices, QVector<QVector<int>> &edges)
{
    FileParser fp;
    return fp.file_parser(nameFile, vertices, edges);
}