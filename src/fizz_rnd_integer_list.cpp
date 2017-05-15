#include "stats.h"
#include "fizz_rnd_integer_list.h"
#include "i_random_number_generator.h"
#include <QtGlobal>

fizz_rnd_integer_list::fizz_rnd_integer_list(int N, i_random_number_generator& rng)
    // initial float list to 0, integer list will be initialized to N
    : fizz_rnd_float_list(0, rng)
{
    initialize(N, rng);
}

fizz_rnd_integer_list::~fizz_rnd_integer_list()
{

}

float fizz_rnd_integer_list::generate_random_number(i_random_number_generator& rng)
{
    return rng.generate_int(0, 1000);
}
