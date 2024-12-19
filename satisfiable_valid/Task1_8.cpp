#include<iostream>

using namespace std;

int main(){
    // DATA EXTRACTION
    // string s;
    // cin>>s;
    // for(int n; n<s.length(); n++){
        
    // }

    bool c,a,h;
    bool satisfiable = 0;
    bool valid = 1;
    bool C,A,H;
     cout<<"C"<<" "<<"A"<<" "<<"H"<<" "<<"notH"<<" "<<"notC"<<" "<<"premises1"<<" "<<"premises2"<<" "<<"conclusion"<<endl;
    for(int c = 0; c<=1; c++){
        for(int a = 0; a<=1; a++){
           for(int h = 0; h<=1; h++){
               C=c;
               A=a;
               H=h;
               bool notH = !H;
               bool notC = !C;

               bool premises1 = C && A;
               bool premises2 = notH || A;
               bool conclusion = H || notC;

               if(premises1 && premises2 && conclusion) satisfiable = 1;
               if(premises1 && premises2){
                  if(!conclusion) valid = 0;
               } 
            
               cout<<C<<" "<<A<<" "<<H<<" "<<notH<<" "<<notC<<" "<<premises1<<" "<<premises2<<" "<<conclusion<<endl;
           } 
        }
    }
    cout<<"Satisfiable: "<<satisfiable<<" Valid: "<<valid<<endl;
}
