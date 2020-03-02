#ifndef LOGICS_H
#define LOGICS_H

#include <QDebug>

#include <fstream>
#include <string>
#include <vector>
#include <utility>

#define FILE_OPENING_ERROR
#define REGION_ERROR

using namespace std;

enum metrics_t {
    minimum,
    maximum,
    median
};

pair<vector<string>, vector<vector<string>>> readCSV(const string &path, const string &region, pair<int, int> years);

vector<string> splitStr(const string &str, const string &sep);

double getMetrics(const vector<vector<string>> &arr, const vector<string> &names, const string &column, metrics_t type);

double getMinimum(const vector<double> &arr);

double getMaximum(const vector<double> &arr);

double getMedian(const vector<double> &arr);

#endif // LOGICS_H
