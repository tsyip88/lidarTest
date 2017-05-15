#include <QString>
#include <QtTest>
#include "fizz_rnd_integer_list.h"
#include "fake_random_number_generator.h"

using namespace QTest;
using namespace std;

Q_DECLARE_METATYPE(vector<int>);
Q_DECLARE_METATYPE(stats);

class tst_fizz_rnd_integer_list : public QObject
{
    Q_OBJECT

public:
    tst_fizz_rnd_integer_list();

private slots:
    void calculates_stats_of_nearest();
    void calculates_stats_of_nearest_data();

private:
    float calculate_standard_deviation(vector<int> values);
    float calculate_mean(vector<int> values);

    fake_random_number_generator rng_;
};

tst_fizz_rnd_integer_list::tst_fizz_rnd_integer_list()
{
}

void tst_fizz_rnd_integer_list::calculates_stats_of_nearest()
{
    QFETCH(vector<int>, random_values);
    QFETCH(float, X);
    QFETCH(stats, expected);
    rng_.set_next_ints(random_values);
    fizz_rnd_integer_list patient(random_values.size(), rng_);

    stats actual = patient.get_stats(X);

//    QCOMPARE(actual.Y, expected.Y);
//    QCOMPARE(actual.M, expected.M);
//    QCOMPARE(actual.mean, expected.mean);
//    QCOMPARE(actual.standard_deviation, expected.standard_deviation);
}

void tst_fizz_rnd_integer_list::calculates_stats_of_nearest_data()
{
    addColumn<vector<int>>("random_values");
    addColumn<float>("X");
    addColumn<stats>("expected");

    vector<int> random_values;
    stats result;
    newRow("No items") << random_values << 12.5f << result;

    random_values = vector<int>({523});
    result.M = 0;
    result.Y = 523;
    result.mean = 523;
    result.standard_deviation = 0.0;
    newRow("Single item") << random_values << 523.0f << result;
    newRow("Single item - below item value") << random_values << 500.0f << result;
    newRow("Single item - above item value") << random_values << 600.0f << result;

    random_values = vector<int>({523, 812});
    result.M = 0;
    result.Y = 523;
    result.mean = 523;
    result.standard_deviation = 0.0;
    newRow("Two items - below value") << random_values << 500.0f << result;
    newRow("Two items - closer to lower") << random_values << 550.0f << result;

    result.M = 1;
    result.Y = 812;
    result.mean = calculate_mean(random_values);
    result.standard_deviation = calculate_standard_deviation(random_values);
    newRow("Two items - closer to upper") << random_values << 723.5f << result;
    newRow("Two items - above top value") << random_values << 923.08f << result;

    random_values = vector<int>({523, 812, 21, 477, 99});
    result.M = 0;
    result.Y = 523;
    result.mean = 523;
    result.standard_deviation = 0.0;
    newRow("Multiple items - first item") << random_values << 501.0f << result;

    result.M = 2;
    result.Y = 21;
    result.mean = calculate_mean(vector<int>({523, 812, 21}));
    result.standard_deviation = calculate_standard_deviation(vector<int>({523, 812, 21}));
    newRow("Multiple items - middle item") << random_values << 22.34f << result;

    result.M = 4;
    result.Y = 99;
    result.mean = calculate_mean(vector<int>({523, 812, 21, 477, 99}));
    result.standard_deviation = calculate_standard_deviation(vector<int>({523, 812, 21, 477, 99}));
    newRow("Multiple items - last item") << random_values << 100.23f << result;
}

float tst_fizz_rnd_integer_list::calculate_standard_deviation(vector<int> values)
{
    float mean = calculate_mean(values);
    float sq_sum = inner_product(values.begin(), values.end(), values.begin(), 0.0);
    float stdev = sqrt(sq_sum / values.size() - mean * mean);
    return stdev;
}

float tst_fizz_rnd_integer_list::calculate_mean(vector<int> values)
{
    return std::accumulate(values.begin(), values.end(), 0.0) / values.size();
}

QTEST_APPLESS_MAIN(tst_fizz_rnd_integer_list)

#include "tst_fizz_rnd_integer_list.moc"
