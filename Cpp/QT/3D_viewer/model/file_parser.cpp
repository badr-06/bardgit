#include "file_parser.h"
#include <QtCore/QDebug>
#include <QtCore/QRegularExpression>
#include <iostream>

minmax FileParser::file_parser(QString str, QVector<QVector<float>>& vertices, QVector<QVector<int>>& edges)
{
    minmax mxy; // структура где хранится Макс и Мин по оси X и Y
    QFile file(str);
    if(file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        QString line = in.readLine();
        
        while(!line.isNull()){
            QStringList list = line.split(QRegularExpression("\\s+"));
            if(list[0] == 'v'){
                QVector<float> vertic = {list[1].toFloat(), list[2].toFloat(), list[3].toFloat()};
                MinMaxFuncion(mxy, vertic); // Функция где нахожу Макс и Мин по оси X и Y
                vertices.push_back(vertic);
                
            } else if(list[0] == 'f'){
                QVector<int> temp;
                for(int i = 1; i < list.size(); ++i){
                    int edge1 = face_extract(list[i]);
                    int edge2;
                if(i+1 < list.size()){
                    edge2 = face_extract(list[i+1]);
                } else {
                    edge2 = face_extract(list[1]);
                }
                temp.push_back(edge1-1);
                temp.push_back(edge2-1);
                }
                edges.push_back(temp);
            } 
            line = in.readLine();
        }
        
    } else {
        qDebug() << "Error file";
    }

    
    file.close();

    return mxy;
}

void FileParser::MinMaxFuncion(minmax &mxy, const QVector<float>& v)
{
    mxy.maxX = qMax(mxy.maxX, v[0]);
    mxy.minX = qMin(mxy.minX, v[0]);
    
    mxy.maxY = qMax(mxy.maxY, v[1]);
    mxy.minY = qMin(mxy.minY, v[1]);

    mxy.maxZ = qMax(mxy.maxZ, v[2]);
    mxy.minZ = qMin(mxy.minZ, v[2]);
}

int FileParser::face_extract(QString str)
{
    int res;
    QString tmp;
    for(int i = 0; i < str.size(); ++i){
        if(str[i] == '/') break;
        tmp += str[i];
    }
    res = tmp.toInt();

    return res;
}

// int main(){
    
//     QVector<QVector<float>> vertices;
//     QVector<QVector<int>> edges;
//     file_parser("../obj/triangle_wire_1.obj", vertices, edges);
    
//     for(int i = 0; i < edges.size(); ++i){
//         for(int j = 0; j < edges[i].size(); ++j){
//             std::cout << edges[i][j] << ' ';
//         }
//         std::cout << std::endl;
//     }

//     return 0;
// }