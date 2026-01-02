#pragma once

#include "../Model/file_ready.h"
#include "../Model/model.h"
#include "../info.h"



// Facade
class Controller : public QObject{

public:
    Controller() : fr() {
        figure_ = fr.getFigure();
    };
    ~Controller() {};

    void LoadVertics(QString str);

    void findCenterModel(minmax& mxy, QVector3D& modelC);
    float findRadiusModel(minmax& mxy);

    Model model;



// ########################################################################################################
// Нужно поместить контроллер в namespace s21
// Загрузки фигуры пока нет
private:
    s21::Figure* figure_;
    FileReady fr;
public:

    s21::Figure* getFigure() { return figure_; }
    // Плоский список вершин
    const float* getVertices() const;
    // Плоский список рёбер
    const unsigned int* getEdges() const;

    // Центр фигуры
    QVector3D getCenter() const;
    // Радиус фигуры
    float getRadius() const;

    const size_t getSizeVertices() const;

    const size_t getSizeEdges() const;

    // Масштабировать и вернуть
    const float* scaled(float scale);
    // Переместить и вернуть
    const float* moved(float dx, float dy, float dz);
    // Повернуть и вернуть
    const float* rotatedX(float angle);
    const float* rotatedY(float angle);
    const float* rotatedZ(float angle);
    
    // Это для вращения мышью, нужно рассчитать вектор оси вращения
    const float* rotated(float angle, float dx, float dy, float dz);
};
