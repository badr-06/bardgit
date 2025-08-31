#pragma once

#include <QApplication>
#include "../model/file_parser.h"

// Facade
class Controller : public QObject{

public:
    Controller() {};
    ~Controller() {};

    minmax LoadVertics(QString str, QVector<QVector<float>>& vertices, QVector<QVector<int>>& edges);
};