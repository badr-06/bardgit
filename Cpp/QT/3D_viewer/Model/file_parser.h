#pragma once

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QString>
#include <QtCore/QVector>
#include <fstream>
#include <iostream>
#include "../info.h"
#include "figure.h"

using namespace s21;

struct quantity_v_f
{
    int V;
    int F;
};

class FileParser {

public:
    FileParser() {};
    ~FileParser() {};

    void file_parser(QString str, Figure& figure);
    void counting_v_f(QString& str, quantity_v_f& quant_vf);
};  