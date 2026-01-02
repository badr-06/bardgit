#pragma once

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QFileDialog>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QTabWidget>
#include <QFrame>
#include <QComboBox>
#include <QCheckBox>
#include <QProgressBar>
#include <QStatusBar>
#include <QToolBar>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QSplitter>
#include <QFont>
#include <QPalette>
#include <QApplication>
#include <filesystem>
#include "openGL.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadModel();
    void resetTransformations();
    void updateMoveX(double value);
    void updateMoveY(double value);
    void updateMoveZ(double value);
    void updateRotateX(double value);
    void updateRotateY(double value);
    void updateRotateZ(double value);
    void updateScale(double value);
    void changeBackgroundColor();
    void toggleWireframe(bool enabled);
    void toggleTextures(bool enabled);
    void about();

private:
    void setupUI();
    void setupMenu();
    void setupToolbar();
    void setupControls();
    void applyStyle();
    
    MyOpenGL* openGLWidget_;
    
    // Основные виджеты
    QWidget* centralWidget_;
    QSplitter* mainSplitter_;
    QTabWidget* controlsTab_;
    
    // Панели управления
    QWidget* transformPanel_;
    QWidget* viewPanel_;
    QWidget* modelPanel_;
    
    // Элементы управления трансформациями
    QDoubleSpinBox* moveXSpin_;
    QDoubleSpinBox* moveYSpin_;
    QDoubleSpinBox* moveZSpin_;
    QDoubleSpinBox* rotateXSpin_;
    QDoubleSpinBox* rotateYSpin_;
    QDoubleSpinBox* rotateZSpin_;
    QDoubleSpinBox* scaleSpin_;
    
    // Слайдеры для более интуитивного управления
    QSlider* moveXSlider_;
    QSlider* moveYSlider_;
    QSlider* moveZSlider_;
    QSlider* rotateXSlider_;
    QSlider* rotateYSlider_;
    QSlider* rotateZSlider_;
    QSlider* scaleSlider_;
    
    // Элементы вида
    QComboBox* projectionCombo_;
    QCheckBox* wireframeCheck_;
    QCheckBox* texturesCheck_;
    QPushButton* bgColorButton_;
    
    // Кнопки действий
    QPushButton* loadButton_;
    QPushButton* resetButton_;
    
    // Статус бар
    QLabel* statusLabel_;
};