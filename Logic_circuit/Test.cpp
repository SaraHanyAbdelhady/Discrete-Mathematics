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
    cout << "Enter the circuit variables (e.g., ABC): ";
    cin >> vars;

    // Input premises
    int numGates;
    cout << "Enter the number of gates: ";
    cin >> numGates;

    vector<string> gates(numGates);
    for (int i = 0; i < numGates-1; ++i) {
        cout << "Enter logical expression for gate" << i + 1 << " (in POST FIX format, e.g., CA&): ";
        cin >> gates[i];
    }

    // Input conclusion
    string unsimplifiedOutput;
    string simplifiedOutput;
    cout << "Enter the unsimplified circuit output (in POST FIX format, e.g., HC|): "; 
    cin >> unsimplifiedOutput;
    cout << "Enter the simplified circuit output (in POST FIX format, e.g., HC|): ";
    cin >> simplifiedOutput;

    // Generate truth table and evaluate expressions
    int numVars = vars.size();
   
    bool equivalent = false;

    cout << "\nTruth Table:\n";
    for(auto v:vars) cout<<v<<" ";
    for (const auto& gate : gates) cout << " " << gate;
    cout << "    " << unsimplifiedOutput <<"     "<<simplifiedOutput<< endl;
     int counter1=0;
     int counter2=0;

    for (int i = 0; i < (1 << numVars); ++i) {
        unordered_map<char, bool> variables;
        for (int j = 0; j < numVars; ++j) {
            variables[vars[j]] = (i >> j) & 1;
        }


        bool unsimplifiedValue = evaluateExpression(unsimplifiedOutput, variables);
        if(unsimplifiedValue) counter1++;

        bool simplifiedValue = evaluateExpression(simplifiedOutput, variables);
        if(simplifiedValue) counter2++;
        
        
        // Print truth table row
        for (char v : vars) cout << variables[v]<< " ";
        for (const auto& gate : gates) cout<<" " << evaluateExpression(gate, variables);
        cout << "  " << unsimplifiedValue <<"     " << simplifiedValue <<endl;
    }
     
     if(counter1==counter2) equivalent=true;
    // Output results
    cout << "\nEquivalent: " << equivalent << endl;
    return 0;
}