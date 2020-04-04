#ifndef LOGICS_UTILS_H
#define LOGICS_UTILS_H

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

// std::string ------------------------------------------------------------------------------------

bool isNumber(const std::string &str);

std::vector <std::string> splitStr(const std::string &str, const std::string &sep);

std::vector <double> svectorToDvector(const std::vector <std::string> &s_vec);

// std::pair --------------------------------------------------------------------------------------

template <typename T>
bool isNumberBetweenPair(T number, std::pair<T, T> pair) {
    // if one member of pair == 0, then compares only to second
    if (!pair.first) {
        return number <= pair.second;
    }
    if (!pair.second) {
        return number >= pair.first;
    }
    return pair.first <= number && number <= pair.second;
}

// std::vector ------------------------------------------------------------------------------------

template <typename T>
size_t getIndex(const std::vector <T> &vec, T elem) {
    auto it = find(vec.begin(), vec.end(), elem);
    if (it == vec.end()) {
        return -1;
    }
    return distance(vec.begin(), it);
}

template <typename T>
double getMinimum(const std::vector <T> &vec) {
    return *std::min_element(vec.begin(), vec.end());
}

template <typename T>
double getMaximum(const std::vector <T> &vec) {
    return *std::max_element(vec.begin(), vec.end());
}

template <typename T>
double getMedian(const std::vector <T> &vec) {
    std::vector <T> tmp_vec(vec);
    std::sort(tmp_vec.begin(), tmp_vec.end());
    if (tmp_vec.size() % 2 == 1) {
        return tmp_vec[tmp_vec.size() / 2];
    }
    return (tmp_vec[tmp_vec.size() / 2] + tmp_vec[tmp_vec.size() / 2 - 1]) / 2;
}

// ------------------------------------------------------------------------------------------------

#endif // LOGICS_UTILS_H
