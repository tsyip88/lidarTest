/*
Lidar C++ Test

Make a class "fizz_rnd_float_list" that, on instantiation, takes a parameter N.  On this instantiation, the class should generate an array,
 named “rand_array”, of size N,
 unordered, floating point random numbers, range 0.0-1.0.

The class should also have a function, call it get_stats(), that takes a parameter X.  This parameter should also be a floating point number,
 range 0.0-1.0.

The function should return 4 items:
1. The value Y in rand_array closest to X.
2. The index M of Y in rand_array.
3. The mean of the values in the list for indexes [0:M]
4. The standard deviation of the values in the list for indexes [0:M].

Write a second class that inherits from "fizz_rnd_float_list", except on instantiation generates rand_array of size N of unordered,
 integer random numbers, range 0-1000.

Then write a working C++ program that takes two user inputs: N and a selector between floating point and fixed point instantiation.
 The program should polymorphically
 select between "fizz_rnd_float_list" and the inherited integer class, based on the command line argument.
 This program should instantiate the class once, with a
 parameter N, and then calls get_stats(X) N+1 times.  On each iteration select X as a random value within the possible
 range of the class’ rand_array.
The program should have two outputs:
 An on screen display of the array on the first line and on each following line the items returned by each get_stat() call.
 A csv formatted file, with a label row, and then output of each get_stat() one line each, on the following lines.

Please write the code in a manner you feel will be the most efficient to run.  Please explain, with comments in the code,
 why you think this is the most efficient.
Please write good code - follow a decent coding standard and add any parameter checks, unit testing, etc. you feel is necessary.
 Please deliver this code via a git repo.
*/

#include <QFile>
#include <QtGlobal>
#include <QScopedPointer>
#include <QDir>
#include <stdio.h>
#include <iostream>
#include "fizz_rnd_float_list.h"
#include "fizz_rnd_integer_list.h"
#include "random_number_generator.h"

using namespace std;

void print_array_data(const vector<float>& data);
void print_stats(float f, const stats& s);
void write_labels(QIODevice* device);
void write_to_file(QIODevice* device, float f, const stats& s);

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);
    random_number_generator rng;
    int N = 0;
    char c;
    printf("Enter a value for N:\n");
    cin >> N;
    printf("Enter 'i' to create an integer list or 'f' to create a float list:\n");
    cin >> c;

    QScopedPointer<fizz_rnd_float_list> fizz_list;
    float lower_range = 0.0;
    float upper_range = 0.0;
    switch(c)
    {
        case 'f':
        {
            fizz_list.reset(new fizz_rnd_float_list(N, rng));
            lower_range = 0.0;
            upper_range = 1.0;
            break;
        }
        case 'i':
        {
            fizz_list.reset(new fizz_rnd_integer_list(N, rng));
            lower_range = 0.0;
            upper_range = 1000.0;
            break;
        }
        default:
        {
            printf("Unrecognized input arg: %c. Failed to run program\n", c);
            return -1;
        }
    }

    print_array_data(fizz_list->rand_array);
    QFile output_file(QDir::currentPath() + "/output.csv");
    bool successfully_opened = output_file.open(QIODevice::WriteOnly);
    if(!successfully_opened)
    {
        printf("Failed to open file: %s\n", qPrintable(output_file.fileName()));
        return -2;
    }
    write_labels(&output_file);
    for(int i = 0; i < N+1; i++)
    {
        float X = rng.generate_float(lower_range, upper_range);
        stats s = fizz_list->get_stats(X);
        print_stats(X, s);
        write_to_file(&output_file, X, s);
    }
    output_file.close();
    printf("Successfully wrote to: %s\n", qPrintable(output_file.fileName()));

    return 0;
}

void print_array_data(const vector<float>& data)
{
    printf("Array Data:\n");
    for(float f : data)
    {
        printf("%s ", qPrintable(QString::number(f)));
    }
    printf("\n");
}

void print_stats(float f, const stats& s)
{
    QString output = QString("getStats(%1): M = %2, Y = %3, mean = %4, std_dev = %5")
            .arg(f).arg(s.M).arg(s.Y).arg(s.mean).arg(s.standard_deviation);
    printf("%s\n", qPrintable(output));
}

void write_labels(QIODevice* device)
{
    QByteArray data("Query,M,Y,Mean,Standard Deviation\n");
    device->write(data);
}

void write_to_file(QIODevice* device, float f, const stats& s)
{
    QString stat_data = QString("%1,%2,%3,%4,%5\n").arg(f).arg(s.M).arg(s.Y).arg(s.mean).arg(s.standard_deviation);
    device->write(stat_data.toUtf8());
}
