#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include "genetic_operators.h"

double generic_genetic_algorithm(unsigned population_size, unsigned generations,
                                 double interval_start, double interval_end, double epsilon, unsigned number_of_dimensions,
                                 double (*calculate_function)(const std::vector<double>& vec));
// adsfasd
#endif