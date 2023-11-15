#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include "genetic_operators.h"

double generic_genetic_algorithm(unsigned population_size, unsigned generations,
                                 double interval_start, double interval_end, double epsilon, unsigned number_of_dimensions,
                                 const unsigned& string_len, double mutation_f, double crossover_probability,
                                 double (*calculate_function)(const std::vector<double>& vec));

#endif