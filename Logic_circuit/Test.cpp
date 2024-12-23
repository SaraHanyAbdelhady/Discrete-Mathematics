#include <bits/stdc++.h>
using namespace std;

// Function to evaluate an Post fix logical expression
bool evaluateExpression(const string& expr, const unordered_map<char,bool>& variables) {
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
    // Input variables
    bool satisfiable=false;
    string vars;
    cout << "Enter the circuit variables (e.g., ABC): ";
    cin >> vars;

    // Input premises
    int numExp;
    cout << "Enter the number of expressions: ";
    cin >> numExp;

    vector<string> Exps(numExp);
    for (int i = 0; i < numExp; ++i) {
        cout << "Enter the logical expression " << i + 1 << " (in POST FIX format, e.g., CA&): ";
        cin >> Exps[i];
    }

    // Input conclusion
    string unsimplifiedOutput;
    string simplifiedOutput;
    cout << "Enter the unsimplified circuit output (in POST FIX format, e.g., HC|): "; 
    cin >> unsimplifiedOutput;
    cout << "Enter the simplified circuit output (in POST FIX format, e.g., HC|): ";
    cin >> simplifiedOutput;

    cout << "Enter the number of simplified circuit variables: ";
    int numSimVars;
    cin>>numSimVars;

    // Generate truth table and evaluate expressions
    int numVars = vars.size();
   
    bool equivalent = false;

    cout << "\nTruth Table:\n";
    for(auto v:vars) cout<<v<<" ";
    for (const auto& exp : Exps) cout << " " << exp;
    cout << "    " << unsimplifiedOutput <<"     "<<simplifiedOutput<<"\n";
    int counter=0;
    vector<int>v;
    for (int i = 0; i < (1 << numVars); i++) {
        unordered_map<char, bool> variables;
        for (int j = 0; j < numVars; j++) {
            variables[vars[j]] = (i >> j) & 1;
        }
      


        bool unsimplifiedValue = evaluateExpression(unsimplifiedOutput, variables);


        bool simplifiedValue = evaluateExpression(simplifiedOutput, variables);
       
        
    if(unsimplifiedValue==1&&simplifiedValue==unsimplifiedValue) 
    {
     satisfiable=true;
     for (char num : vars)  v.push_back(variables[num]);
     counter++;
    }
    else if(unsimplifiedValue==0&&simplifiedValue==unsimplifiedValue){
     counter++;
    }
        
        // Print truth table row
        for (char v : vars) cout << variables[v]<< " ";
        for (const auto& exp : Exps) cout<<" " << evaluateExpression(exp, variables);  
        cout << "  " << unsimplifiedValue <<"     " << simplifiedValue <<"\n";
       
    }

     
     if(counter==pow(2,numVars)) equivalent=true;
    // Output results
    cout << "\nSatisfiable: " << satisfiable << endl;
  if(satisfiable){
cout<<"The input values for the unSimplified expression:"<<endl;
   for(auto v:vars) cout<<v<<" ";
     int count=2;
    while(count--){
        if(count==0)
        cout<<"The input values for the Simplified expression:" ;
    for(int i=0;i<v.size();i++){
        if((i%3)==0)
        cout<<endl;
     if(count==0&&numSimVars<numVars&&(((i+1)%numVars)==0))
       cout<<"X"<<" ";
      else cout<<v[i]<<" "; 
    }
      cout<<endl;
      }}
    cout << "\nEquivalent: " << equivalent << endl;
    return 0;
}