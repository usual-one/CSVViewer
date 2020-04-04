#include "include/logics/logics.h"
#include "include/logics/logics_utils.h"

#include <fstream>
#include <tuple>

vector <string> g_headers = {};
vector <vector<string>> g_fields = {};

static tuple <err_t, double> getMetrics(const string &column, metrics_t type) {
    if (!g_fields.size() || !g_headers.size()) {
        return {DATA_NOT_FOUND, 0};
    }

    if (!column.size()) {
        return {WRONG_COLUMN_NAME, 0};
    }

    int index = -1;

    if (isNumber(column)) {
        index = stoi(column);
    } else {
        index = getIndex(g_headers, column);
    }

    if (index < 0 || index >= (int) g_headers.size()) {
        return {WRONG_COLUMN_NAME, 0};
    }

    vector <string> s_col;
    for (auto it = g_fields.begin(); it != g_fields.end(); it++) {
        if ((*it)[index].size()) {
            s_col.push_back((*it)[index]);
        }
    }
    if (!s_col.size()) {
        return {COLUMN_IS_EMPTY, 0};
    }

    vector <double> d_col = svectorToDvector(s_col);
    if (!d_col.size()) {
        return {INVALID_COLUMN_VALUES, 0};
    }

    switch (type) {
        case MIN:
            return {OK, getMinimum(d_col)};
        case MAX:
            return {OK, getMaximum(d_col)};
        case MEDIAN:
            return {OK, getMedian(d_col)};
        default:
            return {BAD_CODE, 0};
    }
}

static err_t isValid(const vector <string> &record, const string &region, pair<int, int> years) {
    if (years.first != 0 || years.second != 0) {
        if (!record[0].size() || !isNumber(record[0])) {
            return YEARS_NOT_FOUND;
        }
        if (!isNumberBetweenPair(stoi(record[0]), years)) {
            return YEARS_NOT_FOUND;
        }
    }
    if (region.size()) {
        if (!record[1].size()) {
            return REGION_NOT_FOUND;
        }
        if (record[1] != region) {
            return REGION_NOT_FOUND;
        }
    }
    return OK;
}

static tuple <err_t, vector <string>, vector <vector <string>>> readCSV(const string &path, const string &region, pair<int, int> years) {
    ifstream fin(path);
    if (!fin.is_open()) {
        return {FILE_OPENING_ERROR, {}, {}};
    }

    string received_str;
    getline(fin, received_str);
    vector <string> headers = splitStr(received_str, ",");

    vector <vector <string>> records;

    err_t error = OK;
    while (!fin.eof()) {
        getline(fin, received_str);
        vector <string> record = splitStr(received_str, ",");
        if (record.size() != headers.size()) {
            continue;
        }

        error = isValid(record, region, years);
        if (!error) {
            records.push_back(record);
        }
    }
    fin.close();
    if (!records.size()) {
        return {error, {}, {}};
    }
    return {OK, headers, records};
}


res_t exec_op(op_args args) {
    res_t results = {};
    switch (args.operation_type) {
        case LOAD_DATA: {
            auto csv = readCSV(args.path, args.region, args.years);
            results.error_type = get<0>(csv);
            g_headers = results.headers = get<1>(csv);
            g_fields = results.arr = get<2>(csv);
            break;
        }
        case CALCULATE_METRICS: {
            auto metrics = getMetrics(args.column, MIN);
            results.metrics.push_back(get<1>(metrics));
            metrics = getMetrics(args.column, MAX);
            results.metrics.push_back(get<1>(metrics));
            metrics = getMetrics(args.column, MEDIAN);
            results.metrics.push_back(get<1>(metrics));
            results.error_type = get<0>(metrics);
            break;
        }
        default: {
            results.error_type = BAD_CODE;
            break;
        }
    }
    return results;
}
