#include "file_parser.h"
// #include <QtCore/QDebug>
// #include <QtCore/QRegularExpression>
// #include <cctype>
// #include <iostream>

using namespace s21;

void FileParser::file_parser(QString str, Figure& figure)
{
    std::ifstream file(str.toStdString());
    if (!file.is_open()) {
        std::cerr << "Error open file in function file_parser" << std::endl;
        return;
    }
    
    std::string line;
        while(std::getline(file, line)){
            if(line[0] == 'v' && line[1] == ' '){
            const char *c = line.c_str() + 2;
            std::vector<float> vert;
            vert.reserve(3);
            char *end;
            while(*c != '\0')
            {
                while(*c == ' ') c++;

                if(*c == '\0') break;

                float f = std::strtof(c, &end);
                vert.push_back(f);

                c = end;
            }
            figure.addVertex(vert[0], vert[1], vert[2]);
        }
        else if(line[0] == 'f' && line[1] == ' '){
            const char *c = line.c_str() + 2;
            
            std::vector<unsigned int> f;
            f.reserve(10);

            char *end;
            while(*c != '\0')
            {
                while (*c == ' ') c++;

                if(*c == '\0') break;

                long l = std::strtol(c, &end, 10);
                f.push_back(l-1);
                
                c = end;

                while(*c != ' ' && *c != '\0') {
                    c++;
                    std::strtol(c, &end, 10);
                    c = end;
                }

            }
            
            for(int i = 0; i < f.size(); ++i){
                Edge ed;
                if(i == f.size()-1){
                    ed.from = f[i];
                    ed.to = f[0];
                } else {
                    ed.from = f[i];
                    ed.to = f[i+1];
                }
                figure.addEdge(ed.from, ed.to);
            }
        }
        }
        file.close();
}

void FileParser::counting_v_f(QString& str, quantity_v_f& quant_vf)
{
    std::ifstream file(str.toStdString());
    if (!file.is_open()) {
        std::cerr << "Error open file in function counting_v_f" << std::endl;
        return;
    }

    std::string line;
    while (!std::getline(file, line).eof()) {
        
        if (line.empty() || line[0] == '#') continue;

        const char* ptr = line.c_str();
        while (*ptr == ' ' || *ptr == '\t') ++ptr;

        if (*ptr == 'v' && (ptr[1] == ' ' || ptr[1] == '\t')) {
            quant_vf.V++;
        } else if (*ptr == 'f' && (ptr[1] == ' ' || ptr[1] == '\t')) {
            quant_vf.F++;
            
        }
    }

    file.close();
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