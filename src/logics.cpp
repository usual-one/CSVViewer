#include "../include/logics.h"

static bool positiveNumberBetween(int number, int init_number, int final_number) {
    if (init_number == -1 && final_number == -1) {
        return true;
    }
    if (init_number == -1) {
        return number <= final_number;
    }
    if (final_number == -1) {
        return number >= init_number;
    }
    return init_number <= number && number <= final_number;
}

static bool stringCmp(string str, string model) {
    return model == "" || str == model;
}

vector<vector<string>> readCSV(const string &path, const string &region, int init_year, int final_year) {
    ifstream fin(path);
    if (!fin.is_open()) {
        return vector<vector<string>>();
    }

    vector<vector<string>> records;
    string str;

    while (!fin.eof()) {
        getline(fin, str);
        vector<string> record = splitStr(str, ",");
        try {
            if (positiveNumberBetween(stoi(record.at(0)), init_year, final_year) && stringCmp(record.at(1), region)) {
                records.push_back(record);
            }
        } catch (std::invalid_argument) {
            continue;
        }
    }
    return records;
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


