#include "file_parser.h"

using namespace s21;

class FileReady {

    Figure figure_;
    FileParser fp;
    quantity_v_f Quant_vf_;
    
public:
    FileReady() : figure_() {}

    Figure* getFigure() { return &figure_; }
    void reading(QString str);

};