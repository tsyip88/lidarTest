#include "random_number_generator.h"

random_number_generator::random_number_generator()
{

}


float random_number_generator::generate_float(float lower_bound, float upper_bound)
{
    std::uniform_real_distribution<float> dist(lower_bound, upper_bound);
    return dist(mt);
}

int random_number_generator::generate_int(int lower_bound, int upper_bound)
{
    std::uniform_int_distribution<int> dist(lower_bound, upper_bound);
    return dist(mt);
}
