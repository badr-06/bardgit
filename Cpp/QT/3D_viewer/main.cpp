#include <QGuiApplication>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QSceneLoader>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QPointLight>


int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    
    Qt3DExtras::Qt3DWindow view;

    Qt3DCore::QEntity *objectentity = new Qt3DCore::QEntity;
    Qt3DRender::QSceneLoader *sceneloader = new Qt3DRender::QSceneLoader(objectentity);
    sceneloader->setSource(QUrl::fromLocalFile("/home/abdurahman/program/bardgit/Cpp/QT/3D_viewer/obj/cube.obj"));

    
    Qt3DExtras::QPhongMaterial *phongMatrial = new Qt3DExtras::QPhongMaterial(objectentity);

    Qt3DCore::QTransform *sceneTransform = new Qt3DCore::QTransform(objectentity);
    sceneTransform->setScale(5.0f);
    objectentity->addComponent(sceneloader);
    objectentity->addComponent(phongMatrial);
    objectentity->addComponent(sceneTransform);

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(objectentity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("red");
    light->setIntensity(1.0f);
    lightEntity->addComponent(light);

    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(QVector3D(10, 10, 10));
    lightEntity->addComponent(lightTransform);

    view.setRootEntity(objectentity);
    view.show();

    Qt3DRender::QCamera *camera = view.camera();
    camera->lens()->setPerspectiveProjection(60.0f, (float)view.width() / view.height(), 0.1f, 1000.0f);  
    camera->setPosition(QVector3D(0.0f, 0.0f, 40.0f));
    camera->setViewCenter(QVector3D(0.0f, 0.0f, 0.0f));
    
    return app.exec();
}




// #include <QGuiApplication>
// #include <Qt3DExtras/Qt3DWindow>
// #include <Qt3DExtras/QCuboidMesh>
// #include <Qt3DExtras/QPhongMaterial>
// #include <Qt3DRender/QCamera>
// #include <Qt3DRender/QDirectionalLight>
// #include <Qt3DCore/QTransform>

// int main(int argc, char *argv[])
// {
//     QGuiApplication app(argc, argv);

//     Qt3DExtras::Qt3DWindow view;
//     Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity;

//     // Направленный свет с увеличенной интенсивностью
//     Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
//     Qt3DRender::QDirectionalLight *light = new Qt3DRender::QDirectionalLight(lightEntity);
//     light->setColor(Qt::white);
//     light->setIntensity(2.5f);  // Увеличиваем интенсивность
//     lightEntity->addComponent(light);

//     Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform;
//     lightTransform->setRotation(QQuaternion::fromEulerAngles(-30, 45, 0));
//     lightEntity->addComponent(lightTransform);

//     // Куб
//     Qt3DCore::QEntity *cubeEntity = new Qt3DCore::QEntity(rootEntity);
//     Qt3DExtras::QCuboidMesh *cubeMesh = new Qt3DExtras::QCuboidMesh;
//     cubeMesh->setXExtent(2.0f);
//     cubeMesh->setYExtent(2.0f);
//     cubeMesh->setZExtent(2.0f);

//     Qt3DExtras::QPhongMaterial *material = new Qt3DExtras::QPhongMaterial;
//     material->setDiffuse(QColor(255, 0, 0));
//     material->setAmbient(Qt::white);  // Добавляем ambient компонент к материалу
//     material->setSpecular(Qt::white);
//     material->setShininess(100.0f);

//     Qt3DCore::QTransform *transform = new Qt3DCore::QTransform;
//     transform->setTranslation(QVector3D(0, 0, 0));

//     cubeEntity->addComponent(cubeMesh);
//     cubeEntity->addComponent(material);
//     cubeEntity->addComponent(transform);

//     // Камера
//     view.camera()->setPosition(QVector3D(5, 5, 10));
//     view.camera()->setViewCenter(QVector3D(0, 0, 0));
//     view.setRootEntity(rootEntity);

//     view.show();
//     return app.exec();
// }