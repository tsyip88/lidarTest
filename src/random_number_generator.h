#pragma once
#include <random>
#include "i_random_number_generator.h"

class random_number_generator : public i_random_number_generator
{
public:
    random_number_generator();

    float generate_float(float lower_bound, float upper_bound);
    int generate_int(int lower_bound, int upper_bound);

private:
    std::random_device rd;
    std::mt19937 mt;
};
