#ifndef GENETIC_OPERATORS_H
#define GENETIC_OPERATORS_H

#include "random_generators.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

void mutation(std::vector<std::vector<bool>>& population);
/*void crossover(std::vector<std::vector<bool>>& population,
               const double& interval_start, const double& interval_end,
               const double& epsilon, const unsigned& number_of_dimensions,
               double (*calculate_function)(const std::vector<double>& vec));*/
std::vector<std::vector<bool>> selection(const std::vector<std::vector<bool>>& population, unsigned population_size,
                                         const double& interval_start, const double& interval_end,
                                         const double& epsilon, const unsigned& number_of_dimensions,
                                         double (*calculate_function)(const std::vector<double>& vec));
void crossover(std::vector<std::vector<bool>>& population);

#endif