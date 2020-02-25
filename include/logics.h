#ifndef LOGICS_H
#define LOGICS_H

#include <QDebug>

#include <fstream>
#include <string>
#include <vector>

#define FILE_OPENING_ERROR
#define REGION_ERROR

using namespace std;

vector<vector<string>> readCSV(const string &path, const string &region, int init_year, int final_year);

vector<string> splitStr(const string &str, const string &sep);

#endif // LOGICS_H
