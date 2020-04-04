#include "include/logics/logics_utils.h"

// std::string ------------------------------------------------------------------------------------

bool isNumber(const std::string &str) {
    for (auto ch : str) {
        if (!isspace(ch) && !isdigit(ch) && ch != '.' && ch != '-') {
            return false;
        }
    }
    return true;
}

std::vector <std::string> splitStr(const std::string &str, const std::string &sep) {
    std::vector <std::string> arr;
    size_t prev = 0;
    size_t next;
    size_t delta = sep.length();
    while ((next = str.find(sep, prev)) != std::string::npos) {
        arr.push_back(str.substr(prev, next - prev));
        prev = next + delta;
    }
    arr.push_back(str.substr(prev));
    return arr;
}

std::vector <double> svectorToDvector(const std::vector <std::string> &s_vec) {
    std::vector <double> d_vec = {};
    for (auto s : s_vec) {
        if (!s.size()) {
            continue;
        }
        if (isNumber(s)) {
            d_vec.push_back(stod(s));
        } else {
            return {};
        }
    }
    return d_vec;
}

// ------------------------------------------------------------------------------------------------
