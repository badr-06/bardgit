#include "controller.h"

minmax Controller::LoadVertics(QString nameFile, QVector<QVector<float>> &vertices, QVector<QVector<int>> &edges, QVector<float>& flatVertices)
{
    FileReady fr;
    return fr.reading(nameFile, vertices, edges, flatVertices);
}

void Controller::findCenterModel(minmax &mxy, QVector3D& modelC)
{
    model.calculateCenter(mxy, modelC);
}

float Controller::findRadiusModel(minmax &mxy)
{
    return model.calculateRadius(mxy);
}
