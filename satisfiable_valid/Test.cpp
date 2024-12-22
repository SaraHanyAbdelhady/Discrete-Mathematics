#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

// Function to evaluate an RPN logical expression
bool evaluateExpression(const string& expr, const unordered_map<char, bool>& variables) {
    vector<bool> stack;
    for (char c : expr) {
        if (variables.count(c)) {
            // Push variable truth value onto the stack
            stack.push_back(variables.at(c));
        } else if (c == '&') { // Logical AND
            bool b1 = stack.back(); stack.pop_back();
            bool b2 = stack.back(); stack.pop_back();
            stack.push_back(b1 && b2);
        } else if (c == '|') { // Logical OR
            bool b1 = stack.back(); stack.pop_back();
            bool b2 = stack.back(); stack.pop_back();
            stack.push_back(b1 || b2);
        } else if (c == '!') { // Logical NOT
            bool b = stack.back(); stack.pop_back();
            stack.push_back(!b);
        }
    }
    return stack.back();
}

int main() {
    // Input variables
    string vars;
    cout << "Enter variables (e.g., CAH): ";
    cin >> vars;

    // Input premises
    int numPremises;
    cout << "Enter the number of premises: ";
    cin >> numPremises;

    vector<string> premises(numPremises);
    for (int i = 0; i < numPremises; ++i) {
        cout << "Enter premise " << i + 1 << " (in RPN format, e.g., CA&): ";
        cin >> premises[i];
    }

    // Input conclusion
    string conclusion;
    cout << "Enter conclusion (in RPN format, e.g., HC|): ";
    cin >> conclusion;

    // Generate truth table and evaluate expressions
    int numVars = vars.size();
    bool satisfiable = false;
    bool valid = false;

    cout << "\nTruth Table:\n";
    cout << vars;
    for (const auto& premise : premises) cout << "  " << premise;
    cout << "  " << conclusion << endl;
     int counter1=0;
     int counter2=0;

    for (int i = 0; i < (1 << numVars); ++i) {
        unordered_map<char, bool> variables;
        for (int j = 0; j < numVars; ++j) {
            variables[vars[j]] = (i >> j) & 1;
        }

        bool allPremisesTrue = true;
        for (const auto& premise : premises) {
            allPremisesTrue &= evaluateExpression(premise, variables);
        }

        if(allPremisesTrue) counter1++;
       

        bool conclusionValue = evaluateExpression(conclusion, variables);
        if(conclusionValue) counter2++;
        if(allPremisesTrue && conclusionValue) satisfiable = true ;
        
        
        // Print truth table row
        for (char v : vars) cout << variables[v] << " ";
        for (const auto& premise : premises) cout << "  " << evaluateExpression(premise, variables);
        cout << "  " << conclusionValue << endl;
    }
     
     if(counter1==counter2) valid=true;
    // Output results
    cout << "\nSatisfiable: " << satisfiable << endl;
    cout << "Valid: " << valid << endl;

    return 0;
}