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

bool satisfiable=false;
bool tautology=false;
vector<int>v;


stack<bool> truth(string vars,int numExp,string Exp){
stack<bool>st;
 vector<string> Exps(numExp);
 for (int i = 0; i < numExp; ++i) {
        cout << "Enter the logical expression " << i + 1 << " (in POST FIX format, e.g., CA&): ";
        cin >> Exps[i];
    }
     int numVars = vars.size();

     cout << "\nTruth Table:\n";
    for(auto v:vars) cout<<v<<" ";
    for (const auto& exp : Exps) cout << " " << exp;
     cout << "    " <<Exp<<"\n";
    int counter=0;
    int tut=0;
      for (int i = 0; i < (1 << numVars); i++) {
        unordered_map<char, bool> variables;
        for (int j = 0; j < numVars; j++) {
            variables[vars[j]] = (i >> j) & 1;
        }

        bool Value = evaluateExpression(Exp, variables);
        st.push(Value);
       
      if(Value==1) 
    {
     tut++; 
     satisfiable=true;
     for (char num : vars)  v.push_back(variables[num]);
     counter++;
    }

        
        // Print truth table row
        for (char v : vars) cout << variables[v]<< " ";
        for (const auto& exp : Exps) cout<<" " << evaluateExpression(exp, variables);  
        cout << "  " <<Value <<"\n";
     
    }

 if(tut==pow(2,numVars))
     {
        tautology=true;
     }

       return st;
}

string modifyGateForSatisfiability(string expr, const string& vars) {
    int n = expr.size();
    for (int i = 0; i < n; i++) {
        // Check if the current character is an operator
        if (expr[i] == '&' || expr[i] == '|' || expr[i] == '!') {
            string modifiedExpr = expr;

            // Modify the operator
            if (expr[i] == '&') {
                modifiedExpr[i] = '|'; // Change AND to OR
            } else if (expr[i] == '|') {
                modifiedExpr[i] = '&'; // Change OR to AND
            } else if (expr[i] == '!') {
                modifiedExpr.erase(i, 1); // Remove the NOT operator
            }

            // Test the modified expression
              bool isSatisfiable=false; 
            int numVars = vars.size();
            for (int j = 0; j < (1 << numVars); j++) {
                unordered_map<char, bool> variables;
                for (int k = 0; k < numVars; k++) {
                    variables[vars[k]] = (j >> k) & 1;
                }

                if (evaluateExpression(modifiedExpr, variables)) {
                    isSatisfiable = true;
                    break;
                }
            }

            // If satisfiable, return the modified expression
            if (isSatisfiable) {
                return modifiedExpr;
            }
        }
    }

    return ""; // No modification made the circuit satisfiable
}

string modifyGateForNonTautology(string expr, const string& vars) {
    int n = expr.size();
    int numVars = vars.size();
    
    for (int i = 0; i < n; i++) {
        // Check if the current character is an operator
        if (expr[i] == '&' || expr[i] == '|' || expr[i] == '!') {
            string modifiedExpr = expr;

            // Modify the operator
            if (expr[i] == '&') {
                modifiedExpr[i] = '|'; // Change AND to OR
            } else if (expr[i] == '|') {
                modifiedExpr[i] = '&'; // Change OR to AND
            } else if (expr[i] == '!') {
                modifiedExpr.erase(i, 1); // Remove the NOT operator
            }

            // Test the modified expression
            bool isTautology = true; // Assume it's a tautology until proven otherwise
            for (int j = 0; j < (1 << numVars); j++) {
                unordered_map<char, bool> variables;
                for (int k = 0; k < numVars; k++) {
                    variables[vars[k]] = (j >> k) & 1;
                }

                // If any output is false, it is no longer a tautology
                if (!evaluateExpression(modifiedExpr, variables)) {
                    isTautology = false;
                    break;
                }
            }

            // If not a tautology, return the modified expression
            if (!isTautology) {
                return modifiedExpr;
            }
        }
    }

    return ""; // No modification made the circuit non-tautological
}




int main() {
   
    string vars;
    cout << "Enter the circuit variables (e.g., ABC): ";
    cin >> vars;

    
    int numExp;
    cout << "Enter the number of expressions: ";
    cin >> numExp;

    
    string unsimplifiedOutput;
    string simplifiedOutput;
    cout << "Enter the unsimplified circuit output (in POST FIX format, e.g., HC|): "; 
    cin >> unsimplifiedOutput;
    stack<bool>unsimplifiedST;
   unsimplifiedST= truth(vars,numExp,unsimplifiedOutput);

    cout << "Enter the simplified circuit output (in POST FIX format, e.g., HC|): ";
    cin >> simplifiedOutput;
    cout << "Enter the number of simplified circuit variables: ";
    int numSimExp;
    cin>>numSimExp;
    
    stack<bool>simplifiedST;
    simplifiedST=truth(vars,0,simplifiedOutput);

    int numVars = vars.size();
   
    bool equivalent = false;
    while(!simplifiedST.empty())
    {
        if(simplifiedST.top()==unsimplifiedST.top())
        {
            simplifiedST.pop();
            unsimplifiedST.pop();
        }
        else{
            equivalent=false;
            break;
        }
    }
    if(simplifiedST.empty()&&unsimplifiedST.empty())
    {
        equivalent=true;
    }


 
    cout << "\nEquivalent: " << equivalent << endl;
     if(equivalent){
        if(satisfiable&&!tautology){
 cout << "\nSatisfiable: " << satisfiable << endl;
cout<<"The input values for the unSimplified expression:"<<endl;
   for(auto v:vars) cout<<v<<" ";
    for(int i=0;i<v.size();i++){
        if((i%3)==0)
        cout<<endl;
      if(i==v.size()/2)
  cout<<"The input values for the Simplified expression:"<<endl ;
       if((i>=v.size()/2)&&numSimExp<numVars&&(((i+1)%numVars)==0))
       cout<<"X"<<" ";
       else cout<<v[i]<<" "; 
    }

      }
      else if(!satisfiable){
        string s1,s2;
 s1=modifyGateForSatisfiability(unsimplifiedOutput,vars);

  if (!s1.empty()) {
        cout << "Modified Unsimplified circuit output to make it satisfiable: " << s1<< endl;
    } else {
        cout << "Unable to make the circuit satisfiable by changing one gate." << endl;
    }

   s2=modifyGateForSatisfiability(simplifiedOutput,vars); 
     if (!s2.empty()) {
        cout << "Modified simplified circuit output to make it satisfiable: " <<s2 << endl;
    } else {
        cout << "Unable to make the circuit satisfiable by changing one gate." << endl;
    }
    stack<bool>ST;
    stack<bool>ST2;

    bool equi=false;
    ST=truth(vars,numExp,s1);
    ST2=truth(vars,0,s2);

  while(!ST.empty())
    {
        if(ST.top()==ST2.top())
        {
            ST.pop();
            ST2.pop();
        }
        else{
            equi=false;
            break;
        }
    }
    if(ST.empty()&&ST2.empty())
    {
        equi=true;
    }
     cout << "\n Equivalence after changing 1 gate in both circuits: " << equi << endl;
    }else if(tautology){
    string s1,s2;
    s1 = modifyGateForNonTautology(unsimplifiedOutput, vars);
    if (!s1.empty()) {
        cout << "Modified unsimplified circuit output to make it not a tautology: " <<s1 << endl;
    } else {
        cout << "Unable to make the unsimplified circuit not a tautology by changing one gate." << endl;
    }
    s2 = modifyGateForNonTautology(simplifiedOutput, vars);
    if (!s2.empty()) {
        cout << "Modified simplified circuit output to make it not a tautology: " <<s2 << endl;
    } else {
        cout << "Unable to make the simplified circuit not a tautology by changing one gate." << endl;
    }
     stack<bool>ST;
    stack<bool>ST2;

    bool equi=false;
    ST=truth(vars,numExp,s1);
    ST2=truth(vars,0,s2);

  while(!ST.empty())
    {
        if(ST.top()==ST2.top())
        {
            ST.pop();
            ST2.pop();
        }
        else{
            equi=false;
            break;
        }
    }
    if(ST.empty()&&ST2.empty())
    {
        equi=true;
    }
     cout << "\n Equivalence after changing 1 gate in both circuits: " << equi << endl;



}
 
}
   return 0;

}

/***
 * 
Test case 1: (Circuits equivalenr and satisfiable)
Enter the circuit variables (e.g., ABC): ABC
Enter the number of expressions: 7
Enter the unsimplified circuit output (in POST FIX format, e.g., HC|): CB|CA|&BC!|C!A|&&
Enter the logical expression 1 (in POST FIX format, e.g., CA&):  CB|
Enter the logical expression 2 (in POST FIX format, e.g., CA&):  CA|
Enter the logical expression 3 (in POST FIX format, e.g., CA&): CB|CA|&
Enter the logical expression 4 (in POST FIX format, e.g., CA&):  C!
Enter the logical expression 5 (in POST FIX format, e.g., CA&):  C!B|
Enter the logical expression 6 (in POST FIX format, e.g., CA&):  C!A|
Enter the logical expression 7 (in POST FIX format, e.g., CA&):  BC!|AC!|&


Truth Table:
A B C  CB| CA| CB|CA|& C! C!B| C!A| BC!|AC!|&    CB|CA|&BC!|C!A|&&
0 0 0  0 0 0 1 1 1 1  0
1 0 0  0 1 0 1 1 1 1  0
0 1 0  1 0 0 1 1 1 1  0
1 1 0  1 1 1 1 1 1 1  1
0 0 1  1 1 1 0 0 0 0  0
1 0 1  1 1 1 0 0 1 0  0
0 1 1  1 1 1 0 1 0 0  0
1 1 1  1 1 1 0 1 1 1  1
Enter the simplified circuit output (in POST FIX format, e.g., HC|): AB&  
Enter the number of simplified circuit variables: 2

Truth Table:
A B C     AB&
0 0 0   0
1 0 0   0
0 1 0   0
1 1 0   1
0 0 1   0
1 0 1   0
0 1 1   0
1 1 1   1

Equivalent: 1

Satisfiable: 1
The input values for the unSimplified expression:
A B C
1 1 0
1 1 1
The input values for the Simplified expression:
1 1 X
1 1 X

//////////////////////////////////////////////////////////////////////////

Test Case 2:(Circuits Equivalent but not Satisfiable (Contradiction))

Enter the circuit variables (e.g., ABC): ABC
Enter the number of expressions: 0
Enter the unsimplified circuit output (in POST FIX format, e.g., HC|): AB&C&AB&C&!&

Truth Table:
A B C     AB&C&AB&C&!&
0 0 0   0
1 0 0   0
0 1 0   0
1 1 0   0
0 0 1   0
1 0 1   0
0 1 1   0
1 1 1   0
Enter the simplified circuit output (in POST FIX format, e.g., HC|): AB|C|AB|C|!&
Enter the number of simplified circuit variables: 3

Truth Table:
A B C     AB|C|AB|C|!&
0 0 0   0
1 0 0   0
0 1 0   0
1 1 0   0
0 0 1   0
1 0 1   0
0 1 1   0
1 1 1   0

Equivalent: 1
Modified Unsimplified circuit output to make it satisfiable: AB|C&AB&C&!&
Modified simplified circuit output to make it satisfiable: AB|C|AB&C|!&

Truth Table:
A B C     AB|C&AB&C&!&
0 0 0   0
1 0 0   0
0 1 0   0
1 1 0   0
0 0 1   0
1 0 1   1
0 1 1   1
1 1 1   0

Truth Table:
A B C     AB|C|AB&C|!&
0 0 0   0
1 0 0   1
0 1 0   1
1 1 0   0
0 0 1   0
1 0 1   0
0 1 1   0
1 1 1   0

 Equivalence after changing 1 gate in both circuits: 0


//////////////////////////////////////////////////////////////////////////

Test case 3:(circuits Equivalent and tautology)

Enter the circuit variables (e.g., ABC): ABC
Enter the number of expressions: 0
Enter the unsimplified circuit output (in POST FIX format, e.g., HC|): AB|C|AB|C|!|

Truth Table:
A B C     AB|C|AB|C|!|
0 0 0   1
1 0 0   1
0 1 0   1
1 1 0   1
0 0 1   1
1 0 1   1
0 1 1   1
1 1 1   1
Enter the simplified circuit output (in POST FIX format, e.g., HC|): AB&A!B!||
Enter the number of simplified circuit variables: 3

Truth Table:
A B C     AB&A!B!||
0 0 0   1
1 0 0   1
0 1 0   1
1 1 0   1
0 0 1   1
1 0 1   1
0 1 1   1
1 1 1   1

Equivalent: 1
Modified unsimplified circuit output to make it not a tautology: AB&C|AB|C|!|
Modified simplified circuit output to make it not a tautology: AB&AB!||

Truth Table:
A B C     AB&C|AB|C|!|
0 0 0   1
1 0 0   0
0 1 0   0
1 1 0   1
0 0 1   1
1 0 1   1
0 1 1   1
1 1 1   1

Truth Table:
A B C     AB&AB!||
0 0 0   1
1 0 0   1
0 1 0   0
1 1 0   1
0 0 1   1
1 0 1   1
0 1 1   0
1 1 1   1

 Equivalence after changing 1 gate in both circuits: 0


 ***/