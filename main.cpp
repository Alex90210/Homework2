#include "binary_operations.h"
#include "math_functions.h"
#include "genetic_algorithm.h"
#include <iomanip>

int main() {

    double interval_start {-5.12};
    double interval_end {5.12};
    double epsilon {0.0001};

    unsigned number_of_dimensions {30};
    unsigned population_size {100};
    unsigned generations {200};

    auto start_time = std::chrono::high_resolution_clock::now();

    double test = generic_genetic_algorithm(population_size, generations, interval_start, interval_end,
                                            epsilon, number_of_dimensions, rastrigins_function);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time).count();

    std::cout << "Epsilon: " << epsilon << std::endl;
    std::cout << "Generations: " << generations << std::endl;
    std::cout << "Pop size: " << population_size << std::endl;

    std::cout << "rastrigin genetic: " << test << std::endl;
    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Execution time: " << duration << " seconds" << std::endl;

    return 0;
}

/*std::vector<std::vector<bool>> test = generate_population(population_size, interval_start, interval_end, epsilon, number_of_dimensions);


    int x {1};
    for (const auto& i : test) {

        for (auto ii : i) {
            std::cout << ii;
        }
        std::cout << " This was chromosome " << x++;
        std::cout << std::endl;
    }

    x = 1;
    std::vector<double> test_v = evaluate_population(test, interval_start, interval_end, epsilon, number_of_dimensions, rastrigins_function);
    for (const auto& i : test_v) {
        std::cout << "Chromosome " << x++ << " value: "<< i << std::endl;
    }
*/