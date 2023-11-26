#include "random_generators.h"

// using static std::random device is mandatory for effective speed

unsigned get_random_unsigned(unsigned min, unsigned max) {
    static std::random_device rd;
    static std::mt19937 eng(rd());

    std::uniform_int_distribution<unsigned> distribution(min, max);

    return distribution(eng);
}

double get_random_double(double min, double max) { // WAY FASTER
    static bool initialized = false;

    if (!initialized) {
        std::srand(static_cast<unsigned>(std::time(0)));
        initialized = true;
    }

    double random_normalized = static_cast<double>(std::rand()) / RAND_MAX;
    return min + random_normalized * (max - min);
}

/*double get_random_double(double min, double max) { // this is way slower
    static std::random_device rd;
    static std::mt19937_64 eng(rd());

    std::uniform_real_distribution<double> distribution(min, max);

    return distribution(eng);
}*/

/*unsigned get_random_unsigned(unsigned min, unsigned max) {
    static bool initialized = false;

    if (!initialized) {
        std::srand(static_cast<unsigned>(std::time(0)));
        initialized = true;
    }

    return min + std::rand() % (max - min + 1);
}*/

int select_index(const std::vector<double>& cumulative_probabilities) {
    double randomValue = get_random_double(0, 1);

    auto it = std::lower_bound(cumulative_probabilities.begin(), cumulative_probabilities.end(), randomValue);
    int selectedIndex = std::distance(cumulative_probabilities.begin(), it);

    return selectedIndex;
}

std::string random_neighbour(const double& interval_start, const double& interval_end, double epsilon, unsigned number_of_dimensions, std::string& binary_string) {

    std::string copy_string = binary_string;
    unsigned dim_len = dim_binary_length(interval_start, interval_end, epsilon);

    for (size_t i {0}; i < number_of_dimensions; ++i) {
        for (size_t j {i * dim_len}; j < (i + 1) * dim_len; j++) {
            unsigned index = get_random_unsigned(i * dim_len, (i + 1) * dim_len);
            copy_string[index] = (copy_string[index] == '1') ? '0' : '1';
        }
    }

    return copy_string;
}

std::string random_neighbour_one_bit(const std::string& binary_string) {

    std::string copy_string = binary_string;
    unsigned random_index = get_random_unsigned(0, binary_string.length());

    copy_string[random_index] = (copy_string[random_index] == '1') ? '0' : '1';

    return copy_string;
}

std::string next_neighbour(const std::string& binary_string, unsigned index) {

    if (index >= binary_string.length())
        index = get_random_unsigned(0, binary_string.length());
    std::string copy_string = binary_string;

    copy_string[index] = (copy_string[index] == '1') ? '0' : '1';
    ++index;

    return copy_string;
}