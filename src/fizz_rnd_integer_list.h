#pragma once

#include "fizz_rnd_float_list.h"

class fizz_rnd_integer_list : public fizz_rnd_float_list
{
public:
    fizz_rnd_integer_list(int N, i_random_number_generator& rng);
    virtual ~fizz_rnd_integer_list();

protected:
    virtual float generate_random_number(i_random_number_generator& rng);
};
