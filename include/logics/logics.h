#ifndef LOGICS_H
#define LOGICS_H

#include <string>
#include <vector>
#include <utility>

using namespace std;

enum metrics_t {
    MIN,
    MAX,
    MEDIAN
};

enum op_t {
    LOAD_DATA,
    CALCULATE_METRICS
};

enum err_t {
    OK = 0,
    FILE_OPENING_ERROR = 1,
    REGION_NOT_FOUND = 2,
    YEARS_NOT_FOUND = 3,
    WRONG_COLUMN_NAME = 4,
    COLUMN_IS_EMPTY = 5,
    INVALID_COLUMN_VALUES = 6,
    DATA_NOT_FOUND = 7,
    BAD_CODE = 8
};

typedef struct {
    op_t operation_type;
    string path;
    string region;
    pair<int, int> years;
    string column;
} op_args;

typedef struct {
    err_t error_type;
    vector <vector<string>> arr;
    vector <string> headers;
    vector <double> metrics;
} res_t;

res_t exec_op(op_args args);

#endif // LOGICS_H
