#include "binary_operations.h"
#include "math_functions.h"
#include "genetic_algorithm.h"
#include <iomanip>

int main() {

    double interval_start {-5.12};
    double interval_end {5.12};
    double epsilon {0.0001}; // 0.00001 for rastrigin
    unsigned number_of_dimensions {50};
    unsigned string_len = dim_binary_length(interval_start, interval_end, epsilon) * number_of_dimensions;

    unsigned population_size {200};
    unsigned generations {300};
    double mutation_f {10.0}; // 12 for rastrigin
    double crossover_probability {1.0}; // 1 for rastrigin

    std::cout << "Epsilon: " << epsilon << std::endl;
    std::cout << "Generations: " << generations << std::endl;
    std::cout << "Pop size: " << population_size << std::endl;

    const size_t num_runs {30};
    std::vector<double> test_values;
    std::vector<double> execution_times;

    for (size_t i = 0; i < num_runs; ++i) {
        auto start_time = std::chrono::high_resolution_clock::now();

        double test = generic_genetic_algorithm(population_size, generations, interval_start, interval_end,
                                                epsilon, number_of_dimensions, string_len,
                                                mutation_f, crossover_probability,
                                                rastrigins_function);

        std::cout << std::fixed << std::setprecision(5);
        std::cout << "Run " << i + 1 << ": rastrigin genetic: " << test << std::endl;

        // Update test values
        test_values.push_back(test);

        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time).count();
        std::cout << "Execution time: " << duration << " seconds" << std::endl;

        // Update execution times
        execution_times.push_back(duration);
    }

    // Calculate mean
    double mean_test = std::accumulate(test_values.begin(), test_values.end(), 0.0) / num_runs;

    // Calculate median
    std::sort(test_values.begin(), test_values.end());
    double median_test;
    if (num_runs % 2 == 0) {
        median_test = (test_values[num_runs / 2 - 1] + test_values[num_runs / 2]) / 2.0;
    } else {
        median_test = test_values[num_runs / 2];
    }

    // Calculate standard deviation
    double sum_squared_diff = std::accumulate(test_values.begin(), test_values.end(), 0.0,
                                              [mean_test](double acc, double val) {
                                                  return acc + (val - mean_test) * (val - mean_test);
                                              });
    double std_dev_test = std::sqrt(sum_squared_diff / num_runs);

    // Calculate average time
    double average_time = std::accumulate(execution_times.begin(), execution_times.end(), 0.0) / num_runs;

    // Calculate quartiles
    size_t q1_index = num_runs / 4;
    size_t q3_index = 3 * num_runs / 4;
    double q1_test = test_values[q1_index];
    double q3_test = test_values[q3_index];

    // Calculate interquartile range (IQR)
    double iqr = q3_test - q1_test;

    // Output summary
    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Summary:" << std::endl;
    std::cout << "Min test value: " << test_values.front() << std::endl;
    std::cout << "Max test value: " << test_values.back() << std::endl;
    std::cout << "Mean test value: " << mean_test << std::endl;
    std::cout << "Median test value: " << median_test << std::endl;
    std::cout << "Standard deviation of test values: " << std_dev_test << std::endl;
    std::cout << "Average execution time: " << average_time << " seconds" << std::endl;
    std::cout << "Interquartile Range (IQR): " << iqr << std::endl;

    return 0;
}