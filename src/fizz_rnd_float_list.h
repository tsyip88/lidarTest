#pragma once

#include <vector>
#include <random>
#include "stats.h"

class i_random_number_generator;
using namespace std;

class fizz_rnd_float_list
{
public:
    fizz_rnd_float_list(int N, i_random_number_generator& rng);
	virtual ~fizz_rnd_float_list();

    stats get_stats(float X);

    vector<float> rand_array;

protected:
    void initialize(int N, i_random_number_generator& rng);
    virtual float generate_random_number(i_random_number_generator& rng);

private:
    int nearest_index(float X, int left, int right);

    vector<stats> stats_array;
};
