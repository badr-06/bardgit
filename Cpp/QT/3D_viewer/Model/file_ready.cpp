#include "file_ready.h"

void FileReady::reading(QString str)
{   
        figure_.checkQvectors();
        fp.counting_v_f(str, Quant_vf_);
        figure_.select_size(Quant_vf_.V, Quant_vf_.F);
        fp.file_parser(str, figure_);
}

