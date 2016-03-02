#ifndef SORTER_H
#define SORTER_H

#include "mm_colour_enum.h"
#include "servoController.h"

void sorterInit();
void moveSorter(enum mmColours detectedMM);
#endif