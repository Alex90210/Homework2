#include "genetic_algorithm.h"


double generic_genetic_algorithm(unsigned population_size, unsigned generations,
                                 double interval_start, double interval_end, double epsilon, unsigned number_of_dimensions,
                                 const unsigned& string_len, double mutation_f, double crossover_probability,
                                 double (*calculate_function)(const std::vector<double>& vec)) {


    std::vector<std::vector<bool>> population = generate_population(population_size, interval_start, interval_end, epsilon, number_of_dimensions);
    std::vector<double> pop_values = evaluate_population(population, interval_start, interval_end, epsilon, number_of_dimensions, calculate_function);

    auto best_solution = std::min_element(pop_values.begin(), pop_values.end());

    unsigned current_generation {0};
    unsigned k {0};
    while (current_generation < generations) {

        ++current_generation;
        population = selection(population, population_size, interval_start, interval_end, epsilon, number_of_dimensions, calculate_function, k);
        mutation(population, mutation_f, string_len);
        //crossover(population, interval_start, interval_end, epsilon, number_of_dimensions, calculate_function);
        crossover(population, crossover_probability);

        pop_values = evaluate_population(population, interval_start, interval_end, epsilon, number_of_dimensions, calculate_function);
        auto new_best_solution = std::min_element(pop_values.begin(), pop_values.end());
        if (*new_best_solution < *best_solution) {
            best_solution = new_best_solution;
        }

    }

    return static_cast<double>(*best_solution);
}