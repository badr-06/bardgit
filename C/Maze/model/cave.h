#ifndef CAVE_H
#define CAVE_H

#include "model.h"

Date_Cave* get_date_cave();
void cave_generation();
int update_state_cave();
void load_cave(char* filename);
void init_date_cave();

#endif  // HEADER_H