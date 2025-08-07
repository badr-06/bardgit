#include "file_parser.h"
#include <QtCore/QDebug>
#include <QtCore/QRegularExpression>
#include <iostream>

minmax file_parser(QString str, QVector<QVector<float>>& vertices, QVector<QVector<int>>& edges)
{
    minmax mxy; // структура где хранится Макс и Мин по оси X и Y
    QFile file(str);
    if(file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        QString line = in.readLine();
        int i = 1;
        while(!line.isNull()){
            QStringList list = line.split(QRegularExpression("\\s+"));
            qDebug() << i++;
            if(list[0] == 'v'){
                QVector<float> vertic = {list[1].toFloat(), list[2].toFloat(), list[3].toFloat()};
                MinMaxFuncion(mxy, vertic); // Функция где нахожу Макс и Мин по оси X и Y
                vertices.push_back(vertic);
                
            } else if(list[0] == 'f'){
                QVector<int> temp;
                for(int i = 1; i < list.size(); ++i){
                int edge = list[i].front().digitValue();
                temp.push_back(edge-1);
                }
                // std::cout << edge1 << ' ' << edge2 << ' ' << edge3 << ' ' << edge4 << std::endl;
                edges.push_back(temp);
            } 

            line = in.readLine();
        }
    } else {
        qDebug() << "Error file";
    }
    
    file.close();

    // for(auto i : edges){
    //     for(auto to : vertices[i]){
    //         std::cout << to << ' ';
    //     }
    //     std::cout << '\n';
    // }
    // std::cout << mxy.maxX << '\n';
    // std::cout << mxy.minX << '\n';

    // std::cout << mxy.maxY << '\n';
    // std::cout << mxy.minY << '\n';
    
    // std::cout << mxy.maxZ << '\n';
    // std::cout << mxy.minZ << '\n';
    return mxy;
}

void MinMaxFuncion(minmax &mxy, const QVector<float>& v)
{
    mxy.maxX = qMax(mxy.maxX, v[0]);
    mxy.minX = qMin(mxy.minX, v[0]);
    
    mxy.maxY = qMax(mxy.maxY, v[1]);
    mxy.minY = qMin(mxy.minY, v[1]);

    mxy.maxZ = qMax(mxy.maxZ, v[2]);
    mxy.minZ = qMin(mxy.minZ, v[2]);
}

// int main(){
    
//     QVector<QVector<float>> vertices;
//     QVector<int> edges;
//     file_parser("../obj/cube.obj", vertices, edges);
    

//     return 0;
// }