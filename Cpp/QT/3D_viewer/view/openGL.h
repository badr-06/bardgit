#pragma once

#include <QOpenGLWidget>
#include <QApplication>
#include <QWidget>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QVector3D>
#include <QtGui/QMatrix4x4>
#include <QtCore/QtMath>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QSpinBox>
#include "../controller/controller.h"
#include "../info.h"

class MyOpenGL : public QOpenGLWidget, public QOpenGLFunctions {
    QVector<QVector<float>> vertices;
    QVector<QVector<int>> edges;
    QVector3D modelCenter;    // Центр модели
    float modelRadius;        // Радиус ограничивающей сферы
    void calculateCenterRadius(); // Вычисляет центр и радиус
    minmax MaxMinXYZ;
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
    int vertexCount = 0;
    Controller* controller_;
 public:
    MyOpenGL(QWidget *parrent = Q_NULLPTR);
    ~MyOpenGL();
    void initializeGL();
    void resizeGL(int h, int w);
    void paintGL();
    MyOpenGL* GetScene() { return this; };
    void LoadScene(QString nameFile);

    QDoubleSpinBox* scale_x_;
    QDoubleSpinBox* scale_y_;
    QDoubleSpinBox* scale_z_;

};


