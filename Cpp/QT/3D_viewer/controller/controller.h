#pragma once

#include "../model/file_parser.h"
#include "../model/file_ready.h"
#include "../model/model.h"
#include "../info.h"

// Facade
class Controller : public QObject{

public:
    Controller() {};
    ~Controller() {};

    minmax LoadVertics(QString str, QVector<QVector<float>>& vertices, QVector<QVector<int>>& edges, QVector<float>& flatVertices);

    void findCenterModel(minmax& mxy, QVector3D& modelC);
    float findRadiusModel(minmax& mxy);

    Model model; 
};