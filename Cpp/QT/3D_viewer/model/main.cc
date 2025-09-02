#include "file_ready.h"
#include <QVector>
#include <iostream>

int main() {

    FileReady fr;
    QVector<QVector<float>> vertices;
    QVector<QVector<int>> edges;
    QVector<float> flatVertices;
    fr.reading("../obj/tree_915K.obj", vertices, edges, flatVertices);
    std::cerr << "Yes\n";
}