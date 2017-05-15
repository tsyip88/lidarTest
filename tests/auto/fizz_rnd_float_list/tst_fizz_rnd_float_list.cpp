#include <QtTest>
#include <vector>
#include <algorithm>
#include "fizz_rnd_float_list.h"
#include "fake_random_number_generator.h"

using namespace QTest;
using namespace std;

Q_DECLARE_METATYPE(vector<float>);
Q_DECLARE_METATYPE(stats);

class tst_fizz_rnd_float_list : public QObject
{
    Q_OBJECT

public:
    tst_fizz_rnd_float_list(){}
    ~tst_fizz_rnd_float_list(){}

private slots:
    void calculates_stats_of_nearest();
    void calculates_stats_of_nearest_data();

private:
    float calculate_standard_deviation(vector<float> values);
    float calculate_mean(vector<float> values);

    fake_random_number_generator rng_;
};

void tst_fizz_rnd_float_list::calculates_stats_of_nearest()
{
    QFETCH(vector<float>, random_values);
    QFETCH(float, X);
    QFETCH(stats, expected);
    rng_.set_next_floats(random_values);
    fizz_rnd_float_list patient(random_values.size(), rng_);

    stats actual = patient.get_stats(X);

    QCOMPARE(actual.M, expected.M);
    QCOMPARE(actual.Y, expected.Y);
    QCOMPARE(actual.mean, expected.mean);
    QCOMPARE(actual.standard_deviation, expected.standard_deviation);
}

void tst_fizz_rnd_float_list::calculates_stats_of_nearest_data()
{
    addColumn<vector<float>>("random_values");
    addColumn<float>("X");
    addColumn<stats>("expected");

    vector<float> random_values;
    stats result;
    newRow("No items") << random_values << 12.5f << result;

    random_values = vector<float>({12.5f});
    result.M = 0;
    result.Y = 12.5;
    result.mean = 12.5;
    result.standard_deviation = 0.0;
    newRow("Single item") << random_values << 12.5f << result;
    newRow("Single item - below item value") << random_values << 11.3f << result;
    newRow("Single item - above item value") << random_values << 15.2f << result;

    random_values = vector<float>({12.5f, 13.5f});
    result.M = 0;
    result.Y = 12.5;
    result.mean = 12.5;
    result.standard_deviation = 0.0;
    newRow("Two items - below value") << random_values << 11.5f << result;
    newRow("Two items - closer to lower") << random_values << 12.7f << result;

    result.M = 1;
    result.Y = 13.5;
    result.mean = calculate_mean(random_values);
    result.standard_deviation = calculate_standard_deviation(random_values);
    newRow("Two items - closer to upper") << random_values << 13.2f << result;
    newRow("Two items - above top value") << random_values << 14.3f << result;

    random_values = vector<float>({12.5f, 13.5f, 11.0f, 2.0f, 3.0f});
    result.M = 0;
    result.Y = 12.5;
    result.mean = 12.5;
    result.standard_deviation = 0.0;
    newRow("Multiple items - first item") << random_values << 12.6f << result;

    result.M = 2;
    result.Y = 11.0f;
    result.mean = calculate_mean(vector<float>({12.5f, 13.5f, 11.0f}));
    result.standard_deviation = calculate_standard_deviation(vector<float>({12.5f, 13.5f, 11.0f}));
    newRow("Multiple items - middle item") << random_values << 10.8f << result;

    result.M = 4;
    result.Y = 3.0f;
    result.mean = calculate_mean(vector<float>({12.5f, 13.5f, 11.0f, 2.0f, 3.0f}));
    result.standard_deviation = calculate_standard_deviation(vector<float>({12.5f, 13.5f, 11.0f, 2.0f, 3.0f}));
    newRow("Multiple items - last item") << random_values << 3.3f << result;
}

float tst_fizz_rnd_float_list::calculate_standard_deviation(vector<float> v)
{
    float mean = calculate_mean(v);
    float sq_sum = inner_product(v.begin(), v.end(), v.begin(), 0.0);
    float stdev = sqrt(sq_sum / v.size() - mean * mean);
    return stdev;
}

float tst_fizz_rnd_float_list::calculate_mean(vector<float> values)
{
    return std::accumulate(values.begin(), values.end(), 0.0) / values.size();
}

QTEST_APPLESS_MAIN(tst_fizz_rnd_float_list)
#include "tst_fizz_rnd_float_list.moc"
