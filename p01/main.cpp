#include <iostream>
#include <string>
#include <map>
using namespace std;

// 1 true
// 0 false
//yo



int solveEq(std::string& equation) {
    std::cout << equation << std::endl;
    // parantheses
    int openPos = -1;
    for(int i = 0; i < equation.length(); i++) {
        const char& c = equation[i];
        if(openPos == -1 && c == ')') {
            return -1;
        }
        if(c == '(') {
            openPos = i;
            continue;
        }
        if(c == ')') {
            std::string solve = equation.substr(openPos + 1, i - openPos - 1);
            int solved = solveEq(solve);
            std::string result = equation.replace(openPos, i - openPos + 1, std::to_string(solved));
            std::cout << "result " << result << std::endl;
            return solveEq(result);
            return 1;
        }
    }
    // Negations
    for(int i = 0; i < equation.length(); i++) {
        const char& c = equation[i];
        if(c == '~') {
            const char& var = equation[i + 1];
            std::string negated = var == '1' ? "0" : "1";
            return solveEq(equation.replace(i, 2, negated));
        }
    }
    for(int i = 1; i < equation.length(); i++) {
        // Disconjunction V
        const char& c = equation[i];
        if(c == '+') {
            int var1 = equation[i - 1] - 48;
            int var2 = equation[i + 1] - 48;
            equation.replace(i-1, 3, var1 >= 1 || var2 >= 1 ? "1" : "0");
            std::cout << "post disconjunction : " << equation << std::endl;
            return solveEq(equation);
        }
        // Conjunction ^
        if(c == '*') {
            int var1 = equation[i - 1] - 48;
            int var2 = equation[i + 1] - 48;
            equation.replace(i-1, 3, var1 >= 1 && var2 >= 1 ? "1" : "0");
            std::cout << "post conjunction : " << equation << std::endl;
            return solveEq(equation);
        }
        if(i > 2) {
            if(c == '<') {
                int var1 = equation[i - 1] - 48;
                int var2 = equation[i + 1] - 48;
                equation.replace(i-1, 3, var1 >= 1 && var2 >= 1 ? "1" : "0");
                std::cout << "post conjunction : " << equation << std::endl;
                return solveEq(equation);
            }
        }
    }

    std::cout << "final: " << equation << std::endl;

    return 1;
}

std::string cleanWhitespaces(const std::string& str) {
    std::string result;
    for(int i = 0; i < str.length(); i++) {
        const char& c = str[i];
        if(c != ' ') {
            result += c;
        }
    }
    return result;
}

std::string fillVariables(const std::string& str, std::map<char, std::string> map) {
    std::string result = str;
    for(int i = 0; i < result.length(); i++) {
        char& c = result[i];
        if(map.find(c) != map.end()) {
            result.replace(i, 1, map.at(c));
        }
    }
    return result;
}
/*
void printTable(bool (*expr)(int, int)){
    for (int p = 0; p<= 1; p++){
        for(int q = 0; q<= 1; q++){
            bool result = expr(p,q);
            cout << "p: " << p << " q: " << q << " result: " << result << endl;
            
            if(result == 1){
                totCount++;
            }
            if (result == 0){
                contCount++;
            }
            
        }
    }
}
*/
int main() {
    

    const std::string eq1 = "(p + q) + (~p * ~q)";
    const std::string eq2 = "(p <-> q) -> (~p <-> ~q)";
    const std::string eq3 = "(p + q) * (~p + r) -> (p * r)";
    const std::string eq4 = "((p -> r) -> q) <-> (p -> (q -> r))";


    //#1 (p || q) && (!p && !q)
    //#2!(p == q) || (!p == !q);
    //#3 !((p || q) && (!p || r)) || (p && r)
    //#4 (!(!p || r) || q) == (!p || (!q || r))
    
    //printTable(eq1s);
    /* 
    if (totCount == 4){
        cout << "The equation is a tautology" << endl;
    } 
    if (contCount  == 4){
        cout << "The equation is a contradiction" << endl;
    }else if(totCount > 0 && contCount > 0){
        cout << "The equation is contingent" << endl;
    }
    */

    std::string test = fillVariables(cleanWhitespaces(eq1), std::map<char, std::string>{{'p', "0"}, {'q', "0"}});
    solveEq(test);
    
    return 0;

}