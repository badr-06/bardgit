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
    view.lookAt(QVector3D(0, 0, cameraDistance), // Позиция
               QVector3D(0, 0, 0),               // Центр
               QVector3D(0, 1, 0));              // Вектор "вверх"
    //

    QMatrix4x4 model;
    model.translate(-modelCenter);
    model.scale(modelscale);
    QMatrix4x4 final = view * model;
    

    // Применяем матрицы
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(projection.data());
    
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(final.data());

    vao.bind();
    glDrawArrays(GL_LINES, 0, vertexCount);
    vao.release();

}

void MyOpenGL::LoadScene(QString nameFile)
{
    makeCurrent();

    MaxMinXYZ = controller_->LoadVertics(nameFile, vertices, edges, flatVertices);

    vertexCount = flatVertices.size() / 3;

    initVbaVbo();

    controller_->findCenterModel(MaxMinXYZ, modelCenter);
    modelRadius = controller_->findRadiusModel(MaxMinXYZ);
    cameraDistance = modelRadius * 3.0f;

    update();
}

void MyOpenGL::wheelEvent(QWheelEvent *event)
{
    int delta = event->angleDelta().y();
    if(delta == 0) return;

    float scaleFactor = (delta > 0) ? 1.1f : 0.9f;

    for(auto &v : flatVertices){
        v *= scaleFactor;
    }

    initVbaVbo();
    update();
}

void MyOpenGL::initVbaVbo()
{
    vbo.bind();
    vbo.allocate(flatVertices.constData(), flatVertices.size() * sizeof(float));
    vbo.release();


    vao.bind();    
    vbo.bind();
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, nullptr);

    vao.release();
    vbo.release();
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
