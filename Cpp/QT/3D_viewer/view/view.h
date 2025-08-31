#pragma once

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QOpenGLWidget>
#include <QGroupBox>
#include <QFileDialog>
#include "../controller/controller.h"
#include "openGL.h"

class mainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit mainWindow(QWidget *parrent = nullptr);
    ~mainWindow();

private slots:
    void unLoadFile();
    void Scaling();

private:
    void setup();
    void control();

    Controller* Controller_;
    MyOpenGL* myOpengl_;

    // QOpenGLWidget* openglWidget_;

    QPushButton* loadButton_;
};