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


int main() {
    // Input variables
    string vars;
    cout << "Enter the circuit variables (e.g., ABC): ";
    cin >> vars;

    // Input premises
    int numExp;
    cout << "Enter the number of expressions: ";
    cin >> numExp;

    // vector<string> Exps(numExp);
    // for (int i = 0; i < numExp; ++i) {
    //     cout << "Enter the logical expression " << i + 1 << " (in POST FIX format, e.g., CA&): ";
    //     cin >> Exps[i];
    // }

    // Input conclusion
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
    // string simpVars;
    // cout << "Enter the circuit variables (e.g., ABC): ";
    // cin >> simpVars;
    stack<bool>simplifiedST;
   // simplifiedST=truth(simpVars,numSimExp,simplifiedOutput);

    simplifiedST=truth(vars,0,simplifiedOutput);


    // Generate truth table and evaluate expressions
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

    // cout << "\nTruth Table:\n";
    // for(auto v:vars) cout<<v<<" ";
    // for (const auto& exp : Exps) cout << " " << exp;
   // cout << "    " << unsimplifiedOutput <<"     "<<simplifiedOutput<<"\n";
    // int counter=0;
    // vector<int>v;
    // int tut=0;
    // bool tautology=false;
    // for (int i = 0; i < (1 << numVars); i++) {
    //     unordered_map<char, bool> variables;
    //     for (int j = 0; j < numVars; j++) {
    //         variables[vars[j]] = (i >> j) & 1;
    //     }
      


    //     bool unsimplifiedValue = evaluateExpression(unsimplifiedOutput, variables);


    //     bool simplifiedValue = evaluateExpression(simplifiedOutput, variables);
       
        
    // if(unsimplifiedValue==1) 
    // {
    //  tut++; 
    //  satisfiable=true;
    //  for (char num : vars)  v.push_back(variables[num]);
    //  counter++;
    // }
    // else if(unsimplifiedValue==0&&simplifiedValue==unsimplifiedValue){
    //  counter++;
    // }
        
    //     // Print truth table row
    //     for (char v : vars) cout << variables[v]<< " ";
    //     for (const auto& exp : Exps) cout<<" " << evaluateExpression(exp, variables);  
    //     cout << "  " << unsimplifiedValue <<"     " << simplifiedValue <<"\n";
       
    // }

    // if(tut==pow(2,numVars))
    //  {
    //     tautology=true;
    //  }
    //  if(counter==pow(2,numVars)) equivalent=true;
    // Output results
    
 
    cout << "\nEquivalent: " << equivalent << endl;
     if(equivalent){
        if(satisfiable&&!tautology){
 cout << "\nSatisfiable: " << satisfiable << endl;
cout<<"The input values for the unSimplified expression:"<<endl;
   for(auto v:vars) cout<<v<<" ";
     //   cout<<"The input values for the Simplified expression:" ;
    for(int i=0;i<v.size();i++){
        if((i%3)==0)
        cout<<endl;
       if((i>=v.size()/2)&&numSimExp<numVars&&(((i+1)%numVars)==0))
       cout<<"X"<<" ";
       else cout<<v[i]<<" "; 
    }

      }
//       else if(!satisfiable){

//     }else if(tautology){


// }
 
}
   return 0;

}