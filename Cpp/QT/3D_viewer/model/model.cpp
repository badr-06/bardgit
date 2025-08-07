#include "model.h"
#include <algorithm>
#include <iostream>

model::model(QWidget *parent) : QOpenGLWidget(parent)
{

    MaxMinXYZ = file_parser("../obj/cube.obj", vertices, edges);
}

model::~model() {}

void model::calculateCenterRadius()
{
    modelCenter = QVector3D(
        (MaxMinXYZ.minX + MaxMinXYZ.maxX) / 2.0f,
        (MaxMinXYZ.minY + MaxMinXYZ.maxY) / 2.0f,
        (MaxMinXYZ.minZ + MaxMinXYZ.maxZ) / 2.0f
    );

    modelRadius = QVector3D(MaxMinXYZ.maxX-MaxMinXYZ.minX, MaxMinXYZ.maxY-MaxMinXYZ.minY, MaxMinXYZ.maxZ-MaxMinXYZ.minZ).length() / 2.0f;
}

void model::initializeGL()
{
    initializeOpenGLFunctions();  // Инициализация функций OpenGL
    glEnable(GL_DEPTH_TEST);     // Включаем тест глубины для 3D
}

void model::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void model::paintGL()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 projection;
    float aspect = width() / float(height());
    projection.ortho(-modelRadius * aspect, modelRadius * aspect,
                 -modelRadius, modelRadius,
                 -100.0f, 100.0f);

    // Настройка камеры
    QMatrix4x4 view;
    float cameraDistance = modelRadius * 3.0f;
    view.lookAt(QVector3D(0, 0, cameraDistance), // Позиция
               QVector3D(0, 0, 0),               // Центр
               QVector3D(0, 1, 0));              // Вектор "вверх"
    

    // Применяем матрицы
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(projection.data());
    
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(view.data());
    
    glTranslatef(-modelCenter.x(), -modelCenter.y(), -modelCenter.z());

    drawCube();
}

void model::drawCube()
{
    calculateCenterRadius();

    for (auto edg : edges) {
        glBegin(GL_LINE_LOOP);
            for(auto to : edg){
            glVertex3f(vertices[to][0], vertices[to][1], vertices[to][2]);
            }
        glEnd();
    }
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    model glWidget;
    glWidget.resize(800, 600);  // Используем resize() вместо resizeGL()
    glWidget.setWindowTitle("3D Viewer");
    
    glWidget.show();
    return app.exec();
}
