#pragma once

class i_random_number_generator
{
public:
    virtual ~i_random_number_generator(){}

    virtual float generate_float(float lower_bound, float upper_bound) = 0;
    virtual int generate_int(int lower_bound, int upper_bound) = 0;
};
