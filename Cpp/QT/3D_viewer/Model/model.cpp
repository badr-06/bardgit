#include "model.h"
#include <QMatrix2x2>

void Model::calculateCenter(minmax& mxy, QVector3D& modelC)
{
    modelC = QVector3D(
        (mxy.minX + mxy.maxX) / 2.0f,
        (mxy.minY + mxy.maxY) / 2.0f,
        (mxy.minZ + mxy.maxZ) / 2.0f
    );
}

float Model::calculateRadius(minmax &mxy)
{
    return QVector3D(mxy.maxX-mxy.minX, mxy.maxY-mxy.minY, mxy.maxZ-mxy.minZ).length() / 2.0f;
};

