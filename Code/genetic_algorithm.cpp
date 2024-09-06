#include "genetic_algorithm.h"

double adaptive_mutation_probability(double initial_mutation_probability,
                                     double decay_factor, unsigned current_generation) {
    return initial_mutation_probability / (1.0 + decay_factor * current_generation);
    /*return initial_mutation_probability * (1.0 + decay_factor * current_generation);*/
}

double adaptive_crossover_probability(double initial_crossover_probability,
                                      double growth_factor, unsigned current_generation) {
    return initial_crossover_probability * (1.0 + growth_factor * current_generation);
}

double generic_genetic_algorithm(unsigned population_size, unsigned generations,
                                 double interval_start, double interval_end, double epsilon, unsigned number_of_dimensions,
                                 const unsigned& string_len, double mutation_f, double crossover_probability,
                                 double (*calculate_function)(const std::vector<double>& vec)) {


    std::vector<std::vector<bool>> population = generate_population(population_size, interval_start, interval_end, epsilon, number_of_dimensions);
    std::vector<double> pop_values = evaluate_population(population, interval_start, interval_end, epsilon, number_of_dimensions, calculate_function);

    /*auto best_solution = std::min_element(pop_values.begin(), pop_values.end());*/
    double best_solution {1000};

    unsigned no_improvement_gen_counter {0};
    unsigned current_generation {0};
    unsigned elite_pop {170};
    while (current_generation < generations) {

        ++current_generation;
        population = selection(population, population_size, interval_start, interval_end, epsilon, number_of_dimensions, calculate_function, elite_pop);
        if (no_improvement_gen_counter == 3000) {
            mutation(population, 20.0, 100);
            no_improvement_gen_counter = 0;
        }
        else {
             mutation(population, mutation_f, string_len);
            //mutation(population, adaptive_mutation_probability(mutation_f,
            //                                                   0.01, current_generation), string_len);
        }

        // crossover_keep_best(population, interval_start, interval_end, epsilon, number_of_dimensions, calculate_function);
        // crossover_the_best(population, crossover_probability, interval_start, interval_end, epsilon, number_of_dimensions,
        //                           calculate_function);

        double current_crossover_probability = adaptive_crossover_probability(crossover_probability,
                                                                              0.1, current_generation);
        // crossover(population, current_crossover_probability);
        crossover(population, crossover_probability);

        pop_values = evaluate_population(population, interval_start, interval_end, epsilon, number_of_dimensions, calculate_function);
        /*auto new_best_solution = std::min_element(pop_values.begin(), pop_values.end());*/
        double new_best_solution {1000};
        for (auto& i : pop_values)
            if (i < new_best_solution) new_best_solution = i;

        if (new_best_solution < best_solution) {
            best_solution = new_best_solution;
            no_improvement_gen_counter = 0;
        }
        else {
            ++no_improvement_gen_counter;
        }
    }

    /*return static_cast<double>(*best_solution);*/
    return best_solution;
}