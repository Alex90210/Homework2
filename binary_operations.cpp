#include "binary_operations.h"

unsigned dim_binary_length(const double& interval_start, const double& interval_end, double epsilon) {
    unsigned pow_epsilon = 1 / epsilon;
    unsigned dim_number_of_bits = std::ceil(std::log2((interval_end - interval_start) * pow_epsilon));
    return dim_number_of_bits;
}

std::vector<bool> generate_binary_string(const double& interval_start, const double& interval_end, double epsilon, unsigned number_of_dimensions) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    unsigned pow_epsilon = 1 / epsilon;
    unsigned dim_number_of_bits = std::ceil(std::log2((interval_end - interval_start) * pow_epsilon));
    unsigned number_of_bits = number_of_dimensions * dim_number_of_bits;

    std::vector<bool> generated_string;
    for (size_t i = 0; i < number_of_bits; ++i) {
        generated_string.push_back(dis(gen) != 0);
    }

    return generated_string;
}

unsigned binary_to_decimal(const std::vector<bool>& binary_string, const size_t& string_start, const size_t& string_end) {

    unsigned decimal_value {0};
    for (size_t i {string_start}; i < string_end; ++i) {
        decimal_value *= 2;
        decimal_value += binary_string[i];
    }

    return decimal_value;
}

std::vector<double> decode_binary_string(const double& interval_start, const double& interval_end, double epsilon, unsigned number_of_dimensions, const std::vector<bool>& binary_string) {

    // x will be between 0 and 2^n - 1, n is the length of the binary string
    std::vector <double> dimensional_values;
    unsigned dim_length = dim_binary_length(interval_start, interval_end, epsilon);

    for (size_t i {0}; i < number_of_dimensions; ++i) {

        unsigned xb_value = binary_to_decimal(binary_string, dim_length * i, dim_length * (i + 1));
        double x_value = xb_value / (pow(2, dim_length) - 1);

        x_value *= (interval_end - interval_start);
        x_value += interval_start; // x is now between interval_start and interval_end
        dimensional_values.push_back(x_value);
    }

    return dimensional_values;
}

std::vector<std::vector<bool>> generate_population(const unsigned& population_size,
                                          const double& interval_start, const double& interval_end,
                                          const double& epsilon, const unsigned& number_of_dimensions) {

    std::vector<std::vector<bool>> generated_population;

    for (size_t i {0}; i < population_size; ++i) {
        std::vector<bool> temp = generate_binary_string(interval_start, interval_end, epsilon, number_of_dimensions);
        generated_population.push_back(temp);
    }

    return generated_population;
}

std::vector<double> evaluate_population(const std::vector<std::vector<bool>>& population,
                                        const double& interval_start, const double& interval_end,
                                        const double& epsilon, const unsigned& number_of_dimensions,
                                        double (*calculate_function)(const std::vector<double>& vec)) {
    std::vector<double> population_value;

    // this will work for minimizing pozitive functions (i.e. rastrigin)
    for (const auto& i : population) {
        std::vector<double> chromosome_values_for_each_dim = decode_binary_string(interval_start, interval_end, epsilon, number_of_dimensions, i);
        population_value.push_back((calculate_function(chromosome_values_for_each_dim)));
    }

    return population_value;
}