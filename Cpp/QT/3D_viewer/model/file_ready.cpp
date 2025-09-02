#include "file_ready.h"

minmax FileReady::reading(QString str, QVector<QVector<float>>& vertices, QVector<QVector<int>>& edges, QVector<float>& flatVertices)
{
    QFile file(str);

    if(file.open(QIODevice::ReadOnly)){
        fp.file_parser(file, mxy, vertices, edges, flatVertices);
        for (int f = 0; f < edges.size(); ++f) {
            for(auto to : edges[f]){
                for(auto v : vertices[to]){
                    flatVertices.push_back(v);
                }
            }
        }
    } else {
        std::cerr << "Error file";
    }

    
    file.close();

    return mxy;
}