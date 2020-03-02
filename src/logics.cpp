#include "../include/logics.h"

static bool isNumber(const string &str) {
    for (auto it = str.begin(); it != str.end(); it++) {
        if (!isspace(*it) && !isdigit(*it) && *it != '.' && *it != '-') {
            return false;
        }
    }
    return true;
}

static bool positiveNumberBetween(int number, pair<int, int> years) {
    if (!years.first) {
        return number <= years.second;
    }
    if (!years.second) {
        return number >= years.first;
    }
    return years.first <= number && number <= years.second;
}

static bool stringCmp(string str, string model) {
    return str == model;
}

static bool isValid(const vector<string> &record, const string &region, pair<int, int> years) {
    if (years.first != 0 || years.second != 0) {
        if (!record.at(0).size() || !isNumber(record.at(0))) {
            return false;
        }
        if (!positiveNumberBetween(stoi(record.at(0)), years)) {
            return false;
        }
    }
    if (region.size()) {
        if (!record.at(1).size()) {
            return false;
        }
        if (!stringCmp(record.at(1), region)) {
            return false;
        }
    }
    return true;
}

vector<string> splitStr(const string &str, const string &sep)
{
    vector<string> arr;
    size_t prev = 0;
    size_t next;
    size_t delta = sep.length();
    while ((next = str.find(sep, prev)) != string::npos) {
        arr.push_back(str.substr(prev, next - prev));
        prev = next + delta;
    }
    arr.push_back(str.substr(prev));
    return arr;
}

pair<vector<string>, vector<vector<string>>> readCSV(const string &path, const string &region, pair<int, int> years) {
    ifstream fin(path);
    if (!fin.is_open()) {
        return {};
    }

    string received_str;
    getline(fin, received_str);
    vector<string> headers = splitStr(received_str, ",");

    vector<vector<string>> records;

    while (!fin.eof()) {
        getline(fin, received_str);
        vector<string> record = splitStr(received_str, ",");
        if (record.size() != headers.size()) {
            continue;
        }
        if (isValid(record, region, years)) {
            records.push_back(record);
        }
    }
    return {headers, records};
}

static size_t nameToInt(const vector<string> &names, const string &name)
{
    auto it = find(names.begin(), names.end(), name);
    if (it == names.end()) {
        return -1;
    }
    return distance(names.begin(), it);
}

double getMetrics(const vector<vector<string>> &arr, const vector<string> &names, const string &column, metrics_t type) {

    int index = -1;

    if (isNumber(column)) {
        index = stoi(column);
    } else {
        index = nameToInt(names, column);
    }

    if (index < 0 || index >= (int) arr.size()) {
        return -1;
    }

    vector<double> col;

    for (auto it = arr.begin(); it != arr.end(); it++) {
        if (!(*it).at(index).size()) {
            continue;
        }
        if (isNumber((*it).at(index))) {
            col.push_back(stod((*it).at(index)));
        }
    }

    if (!col.size()) {
        return -1;
    }

    switch (type) {
    case minimum:
        return getMinimum(col);
    case maximum:
        return getMaximum(col);
    case median:
        return getMedian(col);
    default:
        return -1;
    }
}

double getMinimum(const vector<double> &arr) {
    return *min_element(arr.begin(), arr.end());
}

double getMaximum(const vector<double> &arr) {
    return *max_element(arr.begin(), arr.end());
}

double getMedian(const vector<double> &arr) {
    if (arr.size() % 2 == 1) {
        return arr.at(arr.size() / 2);
    }
    return (arr.at(arr.size() / 2) + arr.at(arr.size() / 2 - 1)) / 2;
}
