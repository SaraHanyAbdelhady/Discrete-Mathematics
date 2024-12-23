#include <bits/stdc++.h>

using namespace std;

// Function to evaluate an Post fix logical expression
bool evaluateExpression(const string& expr, const unordered_map<char, bool>& variables) {
    stack<bool> st;
    for (char c : expr) {
        if (variables.count(c)) {
            // Push variable onto the stack
            st.push(variables.at(c));
        } else if (c == '&') { //AND
            bool b1 = st.top(); 
            st.pop();
            bool b2 = st.top(); 
            st.pop();
            st.push(b1 && b2);
        } else if (c == '|') { //OR
            bool b1 = st.top(); 
            st.pop();
            bool b2 = st.top(); 
            st.pop();
            st.push(b1 || b2);
        } else if (c == '!') { // NOT
            bool b = st.top();
            st.pop();
            st.push(!b);
        }
    }
    return st.top();
}

int main() {
//Our input sentence:
//I got a new car, and I got a new apartment. I am not happy, or I got a new apartment. Therefore, I am happy, or I don't get a new car. 
//I got a new car = C.
//I got a new apartment = A.
// I am not happy = !H.
//Premises 1 = C&A (INFIX).
//Premises 2 = !H|A (INFIX).
//Conclusion = H|!C  (INFIX).
//These Expressions are Satisfiable.
//These Expressions are invalid.
//The user must transform the 2 premesises and conclusion to Postfix before inputing the data.
 string vars;
 cout << "Enter variables (e.g., CAH): ";
cin >> vars;

    int numPremises=2;
    vector<string> premises(numPremises);
    for (int i = 0; i < numPremises;i++) {
        cout << "Enter premise " << i + 1 << " (in POST FIX format, e.g., CA& or H!A|): ";
        cin >> premises[i];
    }

    // Input conclusion
    string conclusion;
    cout << "Enter conclusion (in POST FIX format, e.g., C!H| ): ";
    cin >> conclusion;

    // Generate truth table and evaluate expressions
    int numVars = vars.size();
    bool satisfiable = false;
    bool valid = false;

    cout << "\nTruth Table:\n";
    for(auto v:vars) cout<<v<<" ";
    for (const auto& premise : premises) cout << "        " << premise;
    cout << "       " << conclusion << endl;


     int counter1=0;
     int counter2=0;
    for (int i = 0; i < (1 << numVars); i++) {
        unordered_map<char, bool> variables;
        for (int j = 0; j < numVars; j++) {
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
        for (char v : vars) cout << variables[v]<< " ";
        for (const auto& premise : premises) cout<<"          " << evaluateExpression(premise, variables);
        cout << "          " << conclusionValue << endl;
    }
     
     if(counter1==counter2) valid=true;
    // Output results
    cout << "\nSatisfiable: " << satisfiable << endl;
    cout << "Valid: " << valid << endl;

    return 0;
}