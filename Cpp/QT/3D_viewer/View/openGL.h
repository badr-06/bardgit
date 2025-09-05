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
    
    QVector3D modelCenter;    // Центр модели
    float modelRadius;        // Радиус ограничивающей сфер 
    QOpenGLBuffer vbo;
    QOpenGLBuffer ebo;
    QOpenGLVertexArrayObject vao;
    int vertexCount = 0;
    Controller* controller_;
    float cameraDistance;
    float modelscale = 1.0f;
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


