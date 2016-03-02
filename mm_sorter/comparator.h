#ifndef COMPARATOR_H
#define COMPARATOR_H
#include "colour_struct.h"
#include "mm_colour_enum.h"

void comparatorInit();
enum mmColours decideColour(struct colour SensorReading);
#endif