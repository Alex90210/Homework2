#include <unordered_map>
#include "genetic_operators.h"

void mutation(std::vector<std::vector<bool>>& population, const double& mutation_f, const unsigned& string_len) {

    // this is incredibly slow
    // const static double mutation_f {1.0};

    static bool message_printed {false};
    if (!message_printed) {
        std::cout << "Mutation p2p: " << mutation_f << std::endl;
        message_printed = true;
    }

    // this is a good start, try: 0.1/L, 2/L, 4/L
    double mutation_probability = mutation_f / string_len;
    for (size_t i {0}; i < population.size(); ++i) {
        for (size_t j {0}; j < population[i].size(); ++j) {
            if (get_random_double(0, 1) <= mutation_probability)
                population[i][j] = ~population[i][j];
        }
    }

}

void crossover_keep_best(std::vector<std::vector<bool>>& population,
               const double& interval_start, const double& interval_end,
               const double& epsilon, const unsigned& number_of_dimensions,
               double (*calculate_function)(const std::vector<double>& vec)) {

    static const double crossover_probability {0.8};

    for (size_t i {0}; i < population.size(); ++i) {
        if (get_random_double(0, 1) <= crossover_probability) {
            for (size_t j {i + 1}; j < population.size(); ++j) {
                if (get_random_double(0, 1) <= crossover_probability) {

                    unsigned chromosome_cut_point = get_random_unsigned(1, population[i].size() - 1);

                    std::vector<bool> parent1 = population[i];
                    std::vector<bool> parent2 = population[j];


                    for (size_t k = chromosome_cut_point; k < population[i].size(); ++k) {
                        bool temp = population[i][k];
                        population[i][k] = population[j][k];
                        population[j][k] = temp;
                    }

                    double fitness_p1 = calculate_function(decode_binary_string(interval_start, interval_end, epsilon, number_of_dimensions, parent1));
                    double fitness_p2 = calculate_function(decode_binary_string(interval_start, interval_end, epsilon, number_of_dimensions, parent2));
                    double fitness_c1 = calculate_function(decode_binary_string(interval_start, interval_end, epsilon, number_of_dimensions, population[i]));
                    double fitness_c2 = calculate_function(decode_binary_string(interval_start, interval_end, epsilon, number_of_dimensions, population[j]));

                    //std::vector<double> values {fitness_p1, fitness_p2, fitness_c1, fitness_c2};

                    if (fitness_p1 > fitness_c1)
                        population[i] = parent1;
                    if (fitness_p2 > fitness_c2)
                        population[j] = parent2;

                    i = j;
                    continue;
                }
            }
        }
    }
}

void crossover(std::vector<std::vector<bool>>& population, const double& crossover_probability) {

    // static const double crossover_probability {0.8};
    static bool message_printed {false};

    if (!message_printed) {
        std::cout << "Crossover prob: " << crossover_probability << std::endl;
        message_printed = true;
    }

    // size_t cut_points {1};
    for (size_t i{ 0 }; i < population.size() - 1; ++i) { // could this -1 fix the segmentation fault?, no
        if (get_random_double(0, 1) <= crossover_probability) {
            for (size_t j{ i + 1 }; j < population.size(); ++j) { // could this cause a segmentation fault?
                if (get_random_double(0, 1) <= crossover_probability) {

                    // this will keep only the children
                    // unsigned chromosome_cut_point {0};
                        unsigned chromosome_cut_point = get_random_unsigned(0, population[i].size() - 1);
                        for (size_t k = chromosome_cut_point; k < population[i].size(); ++k) {
                            bool temp = population[i][k];
                            population[i][k] = population[j][k];
                            population[j][k] = temp;
                        }
                        // could the cut point cause the segmentation fault?

                    i = j;
                    continue;
                }
            }
        }
    }
}

void scale_values(std::vector<double>& values, double min, double max) {
    double currentMin = *std::min_element(values.begin(), values.end());
    double currentMax = *std::max_element(values.begin(), values.end());

    for (double& value : values) {
        value = min + (value - currentMin) * (max - min) / (currentMax - currentMin);
    }
}

void raise_to_power(std::vector<double>& values, double power) {
    for (double& value : values) {
        value = std::pow(value, power);
    }
}

std::vector<std::vector<bool>> elitism(const std::vector<std::vector<bool>>& population,
                                       const std::vector<double>& population_values,
                                       size_t elite_pool) {

    std::vector<size_t> indices(population.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::sort(indices.begin(), indices.end(),
              [&population_values](size_t a, size_t b) {
                  return population_values[a] < population_values[b];
              });

    // Select the top k indices
    std::vector<std::vector<bool>> elite_population;
    for (size_t i = 0; i < elite_pool; ++i) {
        elite_population.push_back(population[indices[i]]);
    }

    return elite_population;
}

std::vector<std::vector<bool>> selection(const std::vector<std::vector<bool>>& population,
                                         unsigned population_size,
                                         const double& interval_start,
                                         const double& interval_end,
                                         const double& epsilon,
                                         const unsigned& number_of_dimensions,
                                         double (*calculate_function)(const std::vector<double>& vec),
                                         size_t k) {
    // Evaluate P
    std::vector<double> population_values = evaluate_population(population, interval_start, interval_end, epsilon, number_of_dimensions, calculate_function);

    // Increase selection pressure
    // this works really well for michawelicz but very bad for schwefels
    scale_values(population_values, 1.0, 2.0);
    raise_to_power(population_values, 2.0); // 10 works well for michalewicz

    // Perform elitism and get the k best chromosomes
    std::vector<std::vector<bool>> elite_population = elitism(population, population_values, k);

    // Total fitness
    double values_sum = std::accumulate(population_values.begin(), population_values.end(), 0.0);

    // Individual probability
    std::vector<double> probability_vector;
    for (const auto& i : population_values) {
        /*probability_vector.push_back((1.0 / (12600 + i)) / values_sum);*/
        probability_vector.push_back( (1.0 / i + epsilon) / values_sum); // g min is in 0
        //probability_vector.push_back( i / values_sum);
    }

    // Normalize probabilities
    double probability_sum = std::accumulate(probability_vector.begin(), probability_vector.end(), 0.0);
    for (auto& probability : probability_vector) {
        probability /= probability_sum;
    }

    // Accumulated probability
    std::vector<double> accumulated_probability_vector;
    std::partial_sum(probability_vector.begin(), probability_vector.end(), std::back_inserter(accumulated_probability_vector));
    accumulated_probability_vector.back() = 1.00;

    // Selection
    std::vector<std::vector<bool>> new_population;
    for (size_t i = 0; i < population_size - k; ++i) {
        int index = select_index(accumulated_probability_vector);
        new_population.push_back(population[index]);
    }

    // Add the elite chromosomes to the new population
    new_population.insert(new_population.end(), elite_population.begin(), elite_population.end());

    return new_population;
}