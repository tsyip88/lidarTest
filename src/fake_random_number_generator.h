#pragma once

#include "i_random_number_generator.h"
#include <vector>
using namespace std;

class fake_random_number_generator : public i_random_number_generator
{
public:
    fake_random_number_generator();

    float generate_float(float lower_bound, float upper_bound);
    int generate_int(int lower_bound, int upper_bound);

    void set_next_floats(const vector<float>& values);
    void set_next_ints(const vector<int>& values);
private:
    vector<float> next_floats_;
    vector<int> next_ints_;
};
