#include "controller.h"

void Controller::LoadVertics(QString nameFile) {

    fr.reading(nameFile);
}

void Controller::findCenterModel(minmax &mxy, QVector3D& modelC) {
    model.calculateCenter(mxy, modelC);
}

float Controller::findRadiusModel(minmax &mxy) {
    return model.calculateRadius(mxy);
}


// ########################################################################################################

// Плоский список вершин
const float* Controller::getVertices() const {
    return figure_->flatVertices();
}

// Плоский список рёбер
const unsigned int* Controller::getEdges() const {
    return figure_->flatEdges();
}

// Центр фигуры
QVector3D Controller::getCenter() const {
    Vector3D vec = figure_->center();
    return QVector3D(vec.x, vec.y, vec.z);
}

// Радиус фигуры
float Controller::getRadius() const {
    return figure_->radius();
}

const size_t Controller::getSizeVertices() const
{
    return figure_->vertices().size();
}

const size_t Controller::getSizeEdges() const
{
    return figure_->edges().size();
}

// Масштабировать и вернуть
const float* Controller::scaled(float scale) {
    return figure_->scale(scale, scale, scale).flatVertices();
}

// Переместить и вернуть
const float* Controller::moved(float dx, float dy, float dz) {
    return figure_->move(dx, dy, dz).flatVertices();
}

// Повернуть и вернуть
const float* Controller::rotatedX(float angle) {
    return figure_->rotate(angle, 1, 0, 0).flatVertices();
}

const float* Controller::rotatedY(float angle) {
    return figure_->rotate(angle, 0, 1, 0).flatVertices();
}

const float* Controller::rotatedZ(float angle) {
    return figure_->rotate(angle, 0, 0, 1).flatVertices();
}

// Это для вращения мышью, нужно рассчитать вектор оси вращения
const float* Controller::rotated(float angle, float dx, float dy, float dz) {
    return figure_->rotate(angle, dx, dy, dz).flatVertices();
}
