#ifndef RANDOM_GENERATORS_H
#define RANDOM_GENERATORS_H

#include "binary_operations.h"
#include <vector>

unsigned get_random_unsigned(unsigned min, unsigned max);
double get_random_double(double min, double max);
int select_index(const std::vector<double>& cumulative_probabilities);
std::string random_neighbour(const double& interval_start, const double& interval_end, double epsilon, unsigned number_of_dimensions, std::string& binary_string);
std::string random_neighbour_one_bit(const std::string& binary_string);
std::string next_neighbour(const std::string& binary_string, unsigned index);
std::string generate_neighbor_n_flipped_bits(const std::string& currentSolution, int bits_to_flip);

#endif