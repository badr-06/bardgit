#include "openGL.h"
#include <algorithm>
#include <iostream>

MyOpenGL::MyOpenGL(QWidget *parent) : controller_(new Controller())
{
}

MyOpenGL::~MyOpenGL() {
    makeCurrent();
    if(vao.isCreated()) vao.destroy();
    if(vbo.isCreated()) vbo.destroy();
    doneCurrent();
}

void MyOpenGL::calculateCenterRadius()
{    
    modelCenter = QVector3D(
        (MaxMinXYZ.minX + MaxMinXYZ.maxX) / 2.0f,
        (MaxMinXYZ.minY + MaxMinXYZ.maxY) / 2.0f,
        (MaxMinXYZ.minZ + MaxMinXYZ.maxZ) / 2.0f
    );
    modelRadius = QVector3D(MaxMinXYZ.maxX-MaxMinXYZ.minX, MaxMinXYZ.maxY-MaxMinXYZ.minY, MaxMinXYZ.maxZ-MaxMinXYZ.minZ).length() / 2.0f;

}

void MyOpenGL::initializeGL()
{
    initializeOpenGLFunctions();  // Инициализация функций OpenGL
    glEnable(GL_DEPTH_TEST);     // Включаем тест глубины для 3D
    


    vbo = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    vbo.create();
    vao.create();

}

void MyOpenGL::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void MyOpenGL::paintGL()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 projection;
    projection.perspective(45.0f, width()/float(height()), 0.1f, 100.0f);
    // QMatrix4x4 projection;
    // float aspect = width() / float(height());
    // projection.ortho(-modelRadius * aspect, modelRadius * aspect,
    //              -modelRadius, modelRadius,
    //              -100.0f, 100.0f);
    
    // Настройка камеры
    QMatrix4x4 view;
    float cameraDistance = modelRadius * 3.0f;
    view.lookAt(QVector3D(0, 0, cameraDistance), // Позиция
               QVector3D(0, 0, 0),               // Центр
               QVector3D(0, 1, 0));              // Вектор "вверх"
    //

    QMatrix4x4 model;
    model.rotate(10.0f, 10.0f, 10.0f);
    // model.scale(0.5f, 0.5f, 0.5f);
    QMatrix4x4 final = view * model;
    

    // Применяем матрицы
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(projection.data());
    
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(final.data());
    
    glTranslatef(-modelCenter.x(), -modelCenter.y(), -modelCenter.z());

    vao.bind();
    glDrawArrays(GL_LINES, 0, vertexCount);
    vao.release();

}

void MyOpenGL::LoadScene(QString nameFile)
{
    makeCurrent();

    MaxMinXYZ = controller_->LoadVertics(nameFile, vertices, edges);


    QVector<float> flatVertices;
    for (int f = 0; f < edges.size(); ++f) {
        for(auto to : edges[f]){
            for(auto v : vertices[to]){
                
                flatVertices.push_back(v);
            }
        }
    }
    edges.clear();
    vertices.clear();

    vertexCount = flatVertices.size() / 3;

    vbo.bind();
    vbo.allocate(flatVertices.constData(), flatVertices.size() * sizeof(float));
    vbo.release();


    vao.bind();    
    vbo.bind();
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, nullptr);

    vao.release();
    vbo.release();

    calculateCenterRadius();

    update();
}

// int main(int argc, char *argv[])
// {
//     QApplication app(argc, argv);

//     MyOpenGL glWidget;
//     glWidget.resize(800, 600);  // Используем resize() вместо resizeGL()
//     glWidget.setWindowTitle("3D Viewer");
    
//     glWidget.show();
//     return app.exec();
// }
