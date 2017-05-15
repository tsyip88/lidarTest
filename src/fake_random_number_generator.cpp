#include "fake_random_number_generator.h"
#include <QtGlobal>

fake_random_number_generator::fake_random_number_generator()
{
}


float fake_random_number_generator::generate_float(float lower_bound, float upper_bound)
{
    Q_UNUSED(lower_bound);
    Q_UNUSED(upper_bound);
    float next_float = next_floats_.front();
    next_floats_.erase(next_floats_.begin());
    return next_float;
}

int fake_random_number_generator::generate_int(int lower_bound, int upper_bound)
{
    Q_UNUSED(lower_bound);
    Q_UNUSED(upper_bound);

    float next_int = next_ints_.front();
    next_ints_.erase(next_ints_.begin());
    return next_int;
}

void fake_random_number_generator::set_next_floats(const vector<float>& values)
{
    next_floats_ = values;
}

void fake_random_number_generator::set_next_ints(const vector<int>& values)
{
    next_ints_ = values;
}
