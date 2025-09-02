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
#include <QMouseEvent>
#include "../controller/controller.h"
#include "../info.h"

class MyOpenGL : public QOpenGLWidget, public QOpenGLFunctions {
    QVector<QVector<float>> vertices;
    QVector<QVector<int>> edges;
    QVector3D modelCenter;    // Центр модели
    float modelRadius;        // Радиус ограничивающей сферы
    minmax MaxMinXYZ;
    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
    int vertexCount = 0;
    Controller* controller_;
    float cameraDistance;
    float modelscale = 1.0f;
    QVector<float> flatVertices;
 public:
    MyOpenGL(QWidget *parrent = Q_NULLPTR);
    ~MyOpenGL();
    void initializeGL() override;
    void resizeGL(int h, int w) override;
    void paintGL() override;
    MyOpenGL* GetScene() { return this; };
    void LoadScene(QString nameFile);
    void wheelEvent(QWheelEvent *event);
    void initVbaVbo();
};


