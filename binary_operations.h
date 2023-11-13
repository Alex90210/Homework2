#ifndef BINARY_OPERATIONS_H
#define BINARY_OPERATIONS_H

#include <iostream>
#include <string>
#include <random>
#include <chrono>

unsigned dim_binary_length(const double& interval_start, const double& interval_end, double epsilon);
unsigned binary_to_decimal(const std::vector<bool>& binary_string, const size_t& string_start, const size_t& string_end);
std::vector<bool> generate_binary_string(const double& interval_start, const double& interval_end, double epsilon, unsigned number_of_dimensions);
std::vector<double> decode_binary_string(const double& interval_start, const double& interval_end, double epsilon, unsigned number_of_dimensions, const std::vector<bool>& binary_string);
std::vector<std::vector<bool>> generate_population(const unsigned& population_size,
                                                   const double& interval_start, const double& interval_end,
                                                   const double& epsilon, const unsigned& number_of_dimensions);
std::vector<double> evaluate_population(const std::vector<std::vector<bool>>& population,
                                        const double& interval_start, const double& interval_end,
                                        const double& epsilon, const unsigned& number_of_dimensions,
                                        double (*calculate_function)(const std::vector<double>& vec));

#endif
