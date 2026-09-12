#include <cstddef>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "UtilString.h"

std::string UtilString::precisionDouble(double db, int precision) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << db;
    return oss.str();
}

std::vector<std::string> UtilString::split(const std::string& str, const char regex) {
    std::vector<std::string> result;
    int start = -1;
    for(std::size_t i = 0; i < str.length(); i++) {
        if(str[i] == regex && start != -1) {
            result.push_back(str.substr(start, i - start));
            start = -1;
        } else if(str[i] != regex && start == -1) {
            start = i;
        }
    }
    if(start != -1) {
        result.push_back(str.substr(start));
    }
    return result;
}

std::string UtilString::addrString(const void* ptr) {
    std::stringstream ss;
    ss << ptr;
    return ss.str();
}
std::string UtilString::padString(int w, const std::string &original, char padding) {
    if(original.length() > w) {
        return original;
    }
    std::stringstream ss;
    int totalPadding = w - original.length();
    int left = ((double) totalPadding / 2) + 0.5;
    int right = totalPadding / 2;
    for(int i = 1; i <= left; i++) {
        ss << padding;
    }
    ss << original;
    for(int i = 1; i <= right; i++) {
        ss << padding;
    }
    return ss.str();
}
std::string UtilString::rightString(int w, const std::string &original, char padding) {
    if(original.length() > w) {
        return original;
    }
    std::stringstream ss;
    std::size_t pads = w - original.length();
    for(std::size_t i = 1; i <= pads; i++) {
        ss << padding;
    }
    ss << original;
    return ss.str();
}

UtilString::Table::Table(
    const std::map<std::string, std::vector<std::string>>& columns,
    const std::vector<std::string>& columnOrder
)
    : columns(columns), columnOrder(columnOrder) {}

void UtilString::Table::print(std::ostream& out) const {
    if(columns.empty()) {
        return;
    }

    std::vector<std::string> headers;
    std::map<std::string, std::size_t> widths;
    std::size_t rowCount = 0;
    if(columnOrder.empty()) {
        for(const auto& [header, values] : columns) {
            headers.push_back(header);
        }
    } else {
        headers = columnOrder;
    }
    for(const std::string& header : headers) {
        const std::vector<std::string>& values = columns.at(header);
        widths[header] = header.length();
        rowCount = std::max(rowCount, values.size());
        for(const std::string& value : values) {
            widths[header] = std::max(widths[header], value.length());
        }
    }

    auto printSeparator = [&]() {
        out << '+';
        for(const std::string& header : headers) {
            out << std::string(widths[header] + 2, '-') << '+';
        }
        out << '\n';
    };
    auto printRow = [&](std::size_t row) {
        out << '|';
        for(const std::string& header : headers) {
            std::string value = row == 0
                ? header
                : row - 1 < columns.at(header).size()
                    ? columns.at(header)[row - 1]
                    : "";
            out << ' ' << padString(static_cast<int>(widths[header]), value, ' ')
                << ' ' << '|';
        }
        out << '\n';
    };

    printSeparator();
    printRow(0);
    printSeparator();
    for(std::size_t row = 1; row <= rowCount; row++) {
        printRow(row);
    }
    printSeparator();
}