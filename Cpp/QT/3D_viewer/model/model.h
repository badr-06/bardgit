#pragma once

#include <QOpenGLWidget>
#include <QApplication>
#include <QWidget>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QVector3D>
#include <QtGui/QMatrix4x4>
#include <QtCore/QtMath>
#include "file_parser.h"

class model : public QOpenGLWidget, protected QOpenGLFunctions {
    QVector<QVector<float>> vertices;
    QVector<QVector<int>> edges;
    QVector3D modelCenter;    // Центр модели
    float modelRadius;        // Радиус ограничивающей сферы
    void calculateCenterRadius(); // Вычисляет центр и радиус
    minmax MaxMinXYZ;
 public:
    model(QWidget *parrent = Q_NULLPTR);
    ~model();
    void initializeGL();
    void resizeGL(int h, int w);
    void paintGL();
    void drawCube();
};


