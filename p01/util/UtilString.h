#pragma once
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <functional>
#include <iostream>

namespace UtilString {
    std::string padString(int width, const std::string& original, char padding); // center string if possible
    std::string precisionDouble(double db, int precision);
    std::vector<std::string> split(const std::string& str, const char regex);
    std::string addrString(const void*);
    std::string rightString(int width, const std::string& original, char padding); // move string to right
    template <typename T>
    std::string arrAsToString(T* arr, int n) {
        std::stringstream ss;
        for(int i = 0; i < n; i++) {
            ss << std::to_string(arr[i]);
            if(i != n - 1) {
                ss << ", ";
            }
        }
        return ss.str();
    }
    template <typename T>
    std::string vectorAsString(std::vector<T> arr) {
        std::stringstream ss;
        int n = arr.size();
        for(int i = 0; i < n; i++) {
            ss << arr[i];
            if(i != n - 1) {
                ss << ", ";
            }
        }
        return ss.str();
    }
    template <typename T>
    std::string vectorAsStringFunc(std::vector<T> arr, std::function<std::string(T& obj)> toString) {
        std::stringstream ss;
        int n = arr.size();
        for(int i = 0; i < n; i++) {
            ss << toString(arr[i]);
            if(i != n - 1) {
                ss << ", ";
            }
        }
        return ss.str();
    }

    struct Table {
        std::map<std::string, std::vector<std::string>> columns;
        std::vector<std::string> columnOrder;

        explicit Table(
            const std::map<std::string, std::vector<std::string>>& columns,
            const std::vector<std::string>& columnOrder = {}
        );
        void print(std::ostream& out = std::cout) const;
    };
};