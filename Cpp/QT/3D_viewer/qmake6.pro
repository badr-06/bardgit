TEMPLATE = app
TARGET = 3d_viewer
QT += 3dcore 3drender 3dinput 3dextras gui

# Для Qt6 используйте:
# QT += 3dcore 3drender 3dinput 3dextras gui

SOURCES += main.cpp

# Укажите путь к вашему OBJ-файлу (замените на актуальный)
RESOURCES += $$files(/home/abdurahman/program/bardgit/Cpp/QT/3D_viewer/obj/cube.obj)

# Дополнительные настройки для Linux
unix {
    QMAKE_CXXFLAGS += -std=c++17
    LIBS += -lassimp
}