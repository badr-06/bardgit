#include "view.h"
#include <QStyleFactory>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    openGLWidget_ = new MyOpenGL();
    setupUI();
    setupMenu();
    setupToolbar();
    setupControls();
    applyStyle();
    
    // Устанавливаем тёмную тему по умолчанию
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    qApp->setPalette(darkPalette);
}

MainWindow::~MainWindow() {
    delete openGLWidget_;
}

void MainWindow::setupUI() {
    centralWidget_ = new QWidget();
    setCentralWidget(centralWidget_);
    
    // Основной splitter для разделения OpenGL и панели управления
    mainSplitter_ = new QSplitter(Qt::Horizontal, centralWidget_);
    
    // Настройка OpenGL виджета
    openGLWidget_->setMinimumSize(800, 600);
    
    // Панель управления с вкладками
    controlsTab_ = new QTabWidget();
    controlsTab_->setMaximumWidth(350);
    
    // Создаем панели для вкладок
    transformPanel_ = new QWidget();
    viewPanel_ = new QWidget();
    modelPanel_ = new QWidget();
    
    controlsTab_->addTab(transformPanel_, "Transform");
    controlsTab_->addTab(viewPanel_, "View");
    controlsTab_->addTab(modelPanel_, "Model");
    
    mainSplitter_->addWidget(openGLWidget_);
    mainSplitter_->addWidget(controlsTab_);
    
    // Настройка пропорций splitter
    mainSplitter_->setStretchFactor(0, 4);
    mainSplitter_->setStretchFactor(1, 1);
    
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget_);
    mainLayout->addWidget(mainSplitter_);
    
    // Статус бар
    statusLabel_ = new QLabel("Ready");
    statusBar()->addWidget(statusLabel_);
}

void MainWindow::setupMenu() {
    QMenu* fileMenu = menuBar()->addMenu("File");
    
    QAction* loadAction = new QAction("Load Model", this);
    loadAction->setShortcut(QKeySequence::Open);
    connect(loadAction, &QAction::triggered, this, &MainWindow::loadModel);
    fileMenu->addAction(loadAction);
    
    QAction* exitAction = new QAction("Exit", this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(exitAction);
    
    QMenu* viewMenu = menuBar()->addMenu("View");
    QAction* resetViewAction = new QAction("Reset View", this);
    connect(resetViewAction, &QAction::triggered, this, &MainWindow::resetTransformations);
    viewMenu->addAction(resetViewAction);
    
    QMenu* helpMenu = menuBar()->addMenu("Help");
    QAction* aboutAction = new QAction("About", this);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
    helpMenu->addAction(aboutAction);
}

void MainWindow::setupToolbar() {
    QToolBar* toolbar = addToolBar("Main Toolbar");
    
    QAction* loadAction = new QAction(QIcon(":/icons/open.png"), "Load Model", this);
    connect(loadAction, &QAction::triggered, this, &MainWindow::loadModel);
    toolbar->addAction(loadAction);
    
    toolbar->addSeparator();
    
    QAction* resetAction = new QAction(QIcon(":/icons/reset.png"), "Reset", this);
    connect(resetAction, &QAction::triggered, this, &MainWindow::resetTransformations);
    toolbar->addAction(resetAction);
}

void MainWindow::setupControls() {
    // Панель трансформаций
    QVBoxLayout* transformLayout = new QVBoxLayout(transformPanel_);
    
    // Группа перемещения
    QGroupBox* moveGroup = new QGroupBox("Position");
    QGridLayout* moveLayout = new QGridLayout(moveGroup);
    
    moveLayout->addWidget(new QLabel("X:"), 0, 0);
    moveXSpin_ = new QDoubleSpinBox();
    moveXSpin_->setRange(-100, 100);
    moveXSpin_->setSingleStep(0.1);
    moveXSpin_->setDecimals(2);
    moveLayout->addWidget(moveXSpin_, 0, 1);
    
    moveXSlider_ = new QSlider(Qt::Horizontal);
    moveXSlider_->setRange(-1000, 1000);
    moveLayout->addWidget(moveXSlider_, 0, 2);
    
    moveLayout->addWidget(new QLabel("Y:"), 1, 0);
    moveYSpin_ = new QDoubleSpinBox();
    moveYSpin_->setRange(-100, 100);
    moveYSpin_->setSingleStep(0.1);
    moveYSpin_->setDecimals(2);
    moveLayout->addWidget(moveYSpin_, 1, 1);
    
    moveYSlider_ = new QSlider(Qt::Horizontal);
    moveYSlider_->setRange(-1000, 1000);
    moveLayout->addWidget(moveYSlider_, 1, 2);
    
    moveLayout->addWidget(new QLabel("Z:"), 2, 0);
    moveZSpin_ = new QDoubleSpinBox();
    moveZSpin_->setRange(-100, 100);
    moveZSpin_->setSingleStep(0.1);
    moveZSpin_->setDecimals(2);
    moveLayout->addWidget(moveZSpin_, 2, 1);
    
    moveZSlider_ = new QSlider(Qt::Horizontal);
    moveZSlider_->setRange(-1000, 1000);
    moveLayout->addWidget(moveZSlider_, 2, 2);
    
    // Группа вращения
    QGroupBox* rotateGroup = new QGroupBox("Rotation");
    QGridLayout* rotateLayout = new QGridLayout(rotateGroup);
    
    rotateLayout->addWidget(new QLabel("X:"), 0, 0);
    rotateXSpin_ = new QDoubleSpinBox();
    rotateXSpin_->setRange(-360, 360);
    rotateXSpin_->setSingleStep(1);
    rotateLayout->addWidget(rotateXSpin_, 0, 1);
    
    rotateXSlider_ = new QSlider(Qt::Horizontal);
    rotateXSlider_->setRange(-3600, 3600);
    rotateLayout->addWidget(rotateXSlider_, 0, 2);
    
    rotateLayout->addWidget(new QLabel("Y:"), 1, 0);
    rotateYSpin_ = new QDoubleSpinBox();
    rotateYSpin_->setRange(-360, 360);
    rotateYSpin_->setSingleStep(1);
    rotateLayout->addWidget(rotateYSpin_, 1, 1);
    
    rotateYSlider_ = new QSlider(Qt::Horizontal);
    rotateYSlider_->setRange(-3600, 3600);
    rotateLayout->addWidget(rotateYSlider_, 1, 2);
    
    rotateLayout->addWidget(new QLabel("Z:"), 2, 0);
    rotateZSpin_ = new QDoubleSpinBox();
    rotateZSpin_->setRange(-360, 360);
    rotateZSpin_->setSingleStep(1);
    rotateLayout->addWidget(rotateZSpin_, 2, 1);
    
    rotateZSlider_ = new QSlider(Qt::Horizontal);
    rotateZSlider_->setRange(-3600, 3600);
    rotateLayout->addWidget(rotateZSlider_, 2, 2);
    
    // Группа масштабирования
    QGroupBox* scaleGroup = new QGroupBox("Scale");
    QHBoxLayout* scaleLayout = new QHBoxLayout(scaleGroup);
    
    scaleSpin_ = new QDoubleSpinBox();
    scaleSpin_->setRange(0.01, 10);
    scaleSpin_->setSingleStep(0.1);
    scaleSpin_->setValue(1.0);
    scaleLayout->addWidget(scaleSpin_);
    
    scaleSlider_ = new QSlider(Qt::Horizontal);
    scaleSlider_->setRange(1, 1000);
    scaleSlider_->setValue(100);
    scaleLayout->addWidget(scaleSlider_);
    
    // Кнопка сброса
    resetButton_ = new QPushButton("Reset Transformations");
    resetButton_->setStyleSheet("QPushButton { background-color: #cc2222ff; color: white; }");
    
    transformLayout->addWidget(moveGroup);
    transformLayout->addWidget(rotateGroup);
    transformLayout->addWidget(scaleGroup);
    transformLayout->addWidget(resetButton_);
    transformLayout->addStretch();
    
    // Панель вида
    QVBoxLayout* viewLayout = new QVBoxLayout(viewPanel_);
    
    QGroupBox* projectionGroup = new QGroupBox("Projection");
    QVBoxLayout* projectionLayout = new QVBoxLayout(projectionGroup);
    projectionCombo_ = new QComboBox();
    projectionCombo_->addItems({"Perspective", "Orthographic"});
    projectionLayout->addWidget(projectionCombo_);
    
    QGroupBox* renderGroup = new QGroupBox("Rendering");
    QVBoxLayout* renderLayout = new QVBoxLayout(renderGroup);
    wireframeCheck_ = new QCheckBox("Wireframe Mode");
    texturesCheck_ = new QCheckBox("Textures");
    texturesCheck_->setChecked(true);
    renderLayout->addWidget(wireframeCheck_);
    renderLayout->addWidget(texturesCheck_);
    
    QGroupBox* bgGroup = new QGroupBox("Background");
    QVBoxLayout* bgLayout = new QVBoxLayout(bgGroup);
    bgColorButton_ = new QPushButton("Change Color");
    bgLayout->addWidget(bgColorButton_);
    
    viewLayout->addWidget(projectionGroup);
    viewLayout->addWidget(renderGroup);
    viewLayout->addWidget(bgGroup);
    viewLayout->addStretch();
    
    // Панель модели
    QVBoxLayout* modelLayout = new QVBoxLayout(modelPanel_);
    
    loadButton_ = new QPushButton("Load 3D Model");
    loadButton_->setStyleSheet("QPushButton { background-color: #1976d2; color: white; font-weight: bold; padding: 8px; }");
    
    modelLayout->addWidget(loadButton_);
    modelLayout->addStretch();
    
    // Подключаем сигналы
    connect(loadButton_, &QPushButton::clicked, this, &MainWindow::loadModel);
    connect(resetButton_, &QPushButton::clicked, this, &MainWindow::resetTransformations);
    
    connect(moveXSpin_, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::updateMoveX);
    connect(moveYSpin_, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::updateMoveY);
    connect(moveZSpin_, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::updateMoveZ);
    
    connect(rotateXSpin_, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::updateRotateX);
    connect(rotateYSpin_, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::updateRotateY);
    connect(rotateZSpin_, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::updateRotateZ);
    
    connect(scaleSpin_, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::updateScale);
    
    connect(bgColorButton_, &QPushButton::clicked, this, &MainWindow::changeBackgroundColor);
    connect(wireframeCheck_, &QCheckBox::toggled, this, &MainWindow::toggleWireframe);
    connect(texturesCheck_, &QCheckBox::toggled, this, &MainWindow::toggleTextures);
    
    // Связываем спинбоксы и слайдеры
    connect(moveXSpin_, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [this](double value) {
        moveXSlider_->setValue(value * 10);
    });
    connect(moveXSlider_, &QSlider::valueChanged, [this](int value) {
        moveXSpin_->setValue(value / 10.0);
    });
    
    // Аналогично для остальных осей...
}

void MainWindow::applyStyle() {
    // Устанавливаем стиль для группы
    QString groupBoxStyle = "QGroupBox { font-weight: bold; border: 1px solid gray; border-radius: 5px; margin-top: 1ex; padding-top: 10px; } "
                           "QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }";
    
    transformPanel_->setStyleSheet(groupBoxStyle);
    viewPanel_->setStyleSheet(groupBoxStyle);
    modelPanel_->setStyleSheet(groupBoxStyle);
}

void MainWindow::loadModel() {
    QString currentPath = QString::fromStdString(std::filesystem::current_path().string());
    QString fileName = QFileDialog::getOpenFileName(this, "Open 3D Model", currentPath, 
                                                   "3D Models (*.obj *.fbx *.dae *.blend *.stl);;"
                                                   "All Files (*)");
    if (!fileName.isEmpty()) {
        openGLWidget_->LoadScene(fileName);
        statusLabel_->setText(QString("Loaded: %1").arg(QFileInfo(fileName).fileName()));
    }
}

void MainWindow::resetTransformations() {
    moveXSpin_->setValue(0);
    moveYSpin_->setValue(0);
    moveZSpin_->setValue(0);
    rotateXSpin_->setValue(0);
    rotateYSpin_->setValue(0);
    rotateZSpin_->setValue(0);
    scaleSpin_->setValue(1.0);
    
    // Сброс в OpenGL виджете
    // openGLWidget_->resetTransformations();
    statusLabel_->setText("Transformations reset");
}

void MainWindow::updateMoveX(double value) {
    // openGLWidget_->moveModel(value, openGLWidget_->getMovePos().y(), openGLWidget_->getMovePos().z());
}

void MainWindow::updateMoveY(double value) {
    // openGLWidget_->moveModel(openGLWidget_->getMovePos().x(), value, openGLWidget_->getMovePos().z());
}

void MainWindow::updateMoveZ(double value) {
    // openGLWidget_->moveModel(openGLWidget_->getMovePos().x(), openGLWidget_->getMovePos().y(), value);
}

void MainWindow::updateRotateX(double value) {
    // openGLWidget_->rotateModel(value, openGLWidget_->getRotatePos().y(), openGLWidget_->getRotatePos().z());
}

void MainWindow::updateRotateY(double value) {
    // openGLWidget_->rotateModel(openGLWidget_->getRotatePos().x(), value, openGLWidget_->getRotatePos().z());
}

void MainWindow::updateRotateZ(double value) {
    // openGLWidget_->rotateModel(openGLWidget_->getRotatePos().x(), openGLWidget_->getRotatePos().y(), value);
}

void MainWindow::updateScale(double value) {
    // openGLWidget_->scaleModel(value);
}

void MainWindow::changeBackgroundColor() {
    QColor color = QColorDialog::getColor(Qt::black, this, "Select Background Color");
    if (color.isValid()) {
        // openGLWidget_->setBackgroundColor(color);
    }
}

void MainWindow::toggleWireframe(bool enabled) {
    // openGLWidget_->setWireframeMode(enabled);
}

void MainWindow::toggleTextures(bool enabled) {
    // openGLWidget_->setTexturesEnabled(enabled);
}

void MainWindow::about() {
    QMessageBox::about(this, "About 3D Viewer", 
                      "<h3>3D Model Viewer</h3>"
                      "<p>A modern 3D model viewer built with Qt and OpenGL.</p>"
                      "<p>Features:</p>"
                      "<ul>"
                      "<li>Load OBJ, FBX, DAE, BLEND, STL files</li>"
                      "<li>Real-time transformations</li>"
                      "<li>Multiple projection modes</li>"
                      "<li>Customizable rendering</li>"
                      "</ul>");
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    std::setlocale(LC_NUMERIC, "C");
    
    MainWindow window;
    window.setWindowTitle("3D Model Viewer");
    window.resize(1400, 900);
    window.show();
    
    return app.exec();
}