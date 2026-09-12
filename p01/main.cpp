#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

std::string solveEq(std::string equation) {
    // parantheses
    std::size_t openPos = -1;
    for(std::size_t i = 0; i < equation.length(); i++) {
        const char& c = equation[i];
        if(openPos == -1 && c == ')') {
            return "-1";
        }
        if(c == '(') {
            openPos = i;
            continue;
        }
        if(c == ')') {
            std::string solve = equation.substr(openPos + 1, i - openPos - 1);
            std::string solved = solveEq(solve);
            std::string result = equation.replace(openPos, i - openPos + 1, solved);
            return solveEq(result);
            return "1";
        }
    }
    // Negations
    for(std::size_t i = 0; i < equation.length(); i++) {
        const char& c = equation[i];
        if(c == '~') {
            const char& var = equation[i + 1];
            std::string negated = var == '1' ? "0" : "1";
            return solveEq(equation.replace(i, 2, negated));
        }
    }
    // Conjunction ^
    for(std::size_t i = 1; i < equation.length() - 1; i++) {
        const char& c = equation[i];
        if(c == '*') {
            int var1 = equation[i - 1] - 48;
            int var2 = equation[i + 1] - 48;
            equation.replace(i-1, 3, var1 >= 1 && var2 >= 1 ? "1" : "0");
            return solveEq(equation);
        }
    }
    // Disconjunction V
    for(std::size_t i = 1; i < equation.length() - 1; i++) {
        const char& c = equation[i];
        if(c == '+') {
            int var1 = equation[i - 1] - 48;
            int var2 = equation[i + 1] - 48;
            equation.replace(i-1, 3, var1 >= 1 || var2 >= 1 ? "1" : "0");
            return solveEq(equation);
        }
    }
    // biconditional <-> (if both are the same)
    for(std::size_t i = 2; i < equation.length() - 1; i++) {
        const char& l = equation[i-1];
        const char& c = equation[i];
        const char& r = equation[i+1];
        if(l == '<' && c == '-' && r == '>') {
                int var1 = equation[i - 2] - 48;
                int var2 = equation[i + 2] - 48;
                equation.replace(i-2, 5, var1 == var2 ? "1" : "0");
                return solveEq(equation);
        }
    }
    // conditional -> (!p || q)
    for(std::size_t i = 2; i < equation.length() - 1; i++) {
        const char& l = equation[i-1];
        const char& c = equation[i];
        if(l == '-' && c == '>') {
                int var1 = equation[i - 2] - 48;
                int var2 = equation[i + 1] - 48;
                equation.replace(i-2, 4, !(var1 == 1) || (var2 == 1) ? "1" : "0");
                return solveEq(equation);
        }
    }

    return equation;

}

std::string cleanWhitespaces(const std::string& str) {
    std::string result;
    for(std::size_t i = 0; i < str.length(); i++) {
        const char& c = str[i];
        if(c != ' ') {
            result += c;
        }
    }
    return result;
}

std::string fillVariables(const std::string& str, std::map<char, std::string> map) {
    std::string result = str;
    for(std::size_t i = 0; i < result.length(); i++) {
        char& c = result[i];
        if(map.find(c) != map.end()) {
            result.replace(i, 1, map.at(c));
        }
    }
    return result;
}

void tryEquation(const std::string& equation, std::vector<char> variables) {
    const std::string cleanedEquation = cleanWhitespaces(equation);
    const std::size_t permutations = 1ULL << variables.size();

    std::cout << "Equation: " << equation << std::endl;

    int truthCount = 0;

    for(std::size_t permutation = 0; permutation < permutations; permutation++) {
        std::map<char, std::string> values;
        for(std::size_t i = 0; i < variables.size(); i++) {
            const char& key = variables[i];
            const char &value = ((permutation >> i) & 1ULL) ? '1' : '0';
            values[key] = value;
            if(i != variables.size() - 1) {
                std::cout << key << ": " << value << ", ";
            } else {
                std::cout << key << ": " << value;
            }
        }
        std::cout << std::endl;
        std::string solved = solveEq(fillVariables(cleanedEquation, values));
        std::cout << "Result: " << solved << std::endl;
        if(solved == "1") {
            truthCount++;
        }
    }
    std::cout << "Truth cases: " << truthCount << "/" << permutations << std::endl << std::endl;
}

int main() {

    const std::string eq1 = "(p + q) + (~p * ~q)";
    const std::string eq2 = "(p <-> q) -> (~p <-> ~q)";
    const std::string eq3 = "(p + q) * (~p + r) -> (p * r)";
    const std::string eq4 = "((p -> r) -> q) <-> (p -> (q -> r))";
    tryEquation(eq1, {'p', 'q'});
    tryEquation(eq2, {'p', 'q'});
    tryEquation(eq3, {'p', 'q'});
    tryEquation(eq4, {'p', 'q', 'r'});

    return 0;

}