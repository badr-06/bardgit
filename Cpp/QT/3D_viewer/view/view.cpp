#include "view.h"

mainWindow::mainWindow(QWidget *parrent) : Controller_(new Controller()), myOpengl_(new MyOpenGL())
{
    setup();
    control();
}


mainWindow::~mainWindow()
{
}

void mainWindow::Scaling()
{
}

void mainWindow::setup()
{

    QWidget* central_widget = new QWidget();
    QHBoxLayout* hbox = new QHBoxLayout(central_widget);

    myOpengl_->setMinimumSize(600, 500);

    QWidget* controls_widget = new QWidget(central_widget);

    loadButton_ = new QPushButton("load model", controls_widget);
    QPushButton* but2_w2 = new QPushButton("model", controls_widget); 
    
    QVBoxLayout* vbox = new QVBoxLayout(controls_widget);

    QGroupBox* Transformation = new QGroupBox("Transformation");
    QGridLayout* transLayot = new QGridLayout(Transformation);

    transLayot->addWidget(new QLabel("Scale: "), 0, 0);
    QDoubleSpinBox* scale_x = new QDoubleSpinBox();
    QDoubleSpinBox* scale_y = new QDoubleSpinBox();
    QDoubleSpinBox* scale_z = new QDoubleSpinBox();

    scale_x->setRange(-100, 100);
    scale_y->setRange(-100, 100);
    scale_z->setRange(-100, 100);
    // scale_x->setSingleStep(0.1);
    // scale_y->setSingleStep(0.1);
    // scale_z->setSingleStep(0.1);

    transLayot->addWidget(scale_x, 0, 1);
    transLayot->addWidget(scale_y, 0, 2);
    transLayot->addWidget(scale_z, 0, 3);

    transLayot->addWidget(new QLabel("Rotate: "), 1, 0);
    QDoubleSpinBox* rotate_x = new QDoubleSpinBox();
    QDoubleSpinBox* rotate_y = new QDoubleSpinBox();
    QDoubleSpinBox* rotate_z = new QDoubleSpinBox();

    rotate_x->setRange(-100, 100);
    rotate_y->setRange(-100, 100);
    rotate_z->setRange(-100, 100);
    // rotate_x->setSingleStep(0.1);
    // rotate_y->setSingleStep(0.1);
    // rotate_z->setSingleStep(0.1);

    transLayot->addWidget(rotate_x, 1, 1);
    transLayot->addWidget(rotate_y, 1, 2);
    transLayot->addWidget(rotate_z, 1, 3);

    vbox->addWidget(loadButton_);
    vbox->addWidget(but2_w2);
    vbox->addWidget(Transformation);

    hbox->addWidget(myOpengl_);
    hbox->addWidget(controls_widget);

    setCentralWidget(central_widget);
}

void mainWindow::control()
{
    QObject::connect(loadButton_, SIGNAL(clicked()), this, SLOT(unLoadFile()));

}

void mainWindow::unLoadFile()
{
    QString nameFile = QFileDialog::getOpenFileName(this, "Open File", "/home/abdurahman/program/bardgit/Cpp/QT/3D_viewer/obj", "Object name (*.obj)");
    if(!nameFile.isEmpty()){
        myOpengl_->LoadScene(nameFile);
    } else {
        qDebug() << "error open file";
    }
}

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    mainWindow w;
    w.resize(1000, 800);
    w.show();
    return app.exec();
}