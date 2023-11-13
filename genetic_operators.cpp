#include "genetic_operators.h"

void mutation(std::vector<std::vector<bool>>& population) {
    // this is a good start, try: 0.1/L, 2/L, 4/L
    double mutation_probability = 1.0 / population.at(0).size();
    for (size_t i {0}; i < population.size(); ++i) {
        for (size_t j {0}; j < population[i].size(); ++j) {
            if (get_random_double(0, 1) <= mutation_probability)
                population[i][j] = ~population[i][j];
        }
    }
}

// this variant will only keep the children and do "crossover" only with parents after the i parent
// should I implement a map for checking the "crossover status"?
// If I test one chromosome more than 1 time, the probability to choose the respective chromosome
// will become higher
void crossover(std::vector<std::vector<bool>>& population) {
    // two parents enter crossover, exit however many I want
    // the best 2 out of 4 sounds like a good idea
    // don't use crossover more than 1 time for a parent in a single generation
    // crossover probability 30% - 80%

    static const double crossover_probability {0.3};

    for (size_t i {0}; i < population.size(); ++i) {
        if (get_random_double(0, 1) <= crossover_probability) {
            for (size_t j {i + 1}; j < population.size(); ++j) {
                if (get_random_double(0, 1) <= crossover_probability) {
                    // now crossover can happen
                    // between pop[i] and pop[j]

                    unsigned chromosome_cut_point = get_random_unsigned(1, population[i].size() - 1);
                    // maybe I should create a new population vector

                    // this will keep only the children
                    for (size_t k = chromosome_cut_point; k < population[i].size(); ++k) {
                        bool temp = population[i][k];
                        population[i][k] = population[j][k];
                        population[j][k] = temp;
                    }
                }
            }
        }
    }
}

std::vector<std::vector<bool>> selection(const std::vector<std::vector<bool>>& population, unsigned population_size,
               const double& interval_start, const double& interval_end,
               const double& epsilon, const unsigned& number_of_dimensions,
               double (*calculate_function)(const std::vector<double>& vec)) {

    // 1. assign a value for each chromosome
    // this will only work for positive functions: de jong 1, rastrigin: f_value = 1 / f(x)
    // if the function is negative: constant - f(x)

    // evaluate P
    std::vector<double> population_values = evaluate_population(population, interval_start, interval_end, epsilon, number_of_dimensions, calculate_function);

    // I don't really know how to apply the first step correction

    // total fitness
    double values_sum {0};
    for(auto& i : population_values) {
        values_sum += i;
    }

    // individual probability
    std::vector<double> probability_vector;
    for (auto& i : population_values) {
        probability_vector.push_back( (1.0 / (12600 + i)) / values_sum);
    }


    // accumulated probability
    double sum{0}; // I probably could very easily modify the first vector
    std::vector<double> accumulated_probability_vector;
    for (const double& probability : probability_vector) {
        sum += probability;
        accumulated_probability_vector.push_back(sum);
    }
    accumulated_probability_vector[accumulated_probability_vector.size() - 1] = 1.00;


    // selection
    std::vector<std::vector<bool>> new_population;
    for (size_t i {0}; i < population_size; ++i) {
        int index = select_index(accumulated_probability_vector);
        new_population.push_back(population[index]);
    }

    return new_population;
}