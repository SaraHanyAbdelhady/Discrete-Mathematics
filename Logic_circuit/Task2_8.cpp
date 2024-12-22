#include<bits/stdc++.h>

using namespace std;

int main(){

     bool A,B,C;
     bool equivalent=1;
     vector<int>v;
     cout<<"A"<<"       "<<"B"<<"     "<<"C"<<"    "<<"~C"<<"    "<<"B||C"<<"    "<<"A||C"<<"  "<<"(B||C)&&(A||C)"<<"  "<<"B||~C"<<" "<<"A||~C"<<" "<<"(B||~C)and(A||~C)"<<"    "<<"Unsimplified Expression"<<"       "<<"Simplified Expression(A&&B)"<<endl;
      for(int a = 0; a<=1; a++){
        for(int b = 0; b<=1; b++){
           for(int c = 0; c<=1; c++){
               A=a;
               B=b;
               C=c;
               bool notC = !C;
               bool BorC=B||C;
               bool AorC=A||C;
               bool exp1 = BorC && AorC;
               bool BorNotC= B||(notC);
               bool AorNotC= A ||(notC);
               bool exp2=BorNotC&&AorNotC;
               bool unsimplified=exp1 && exp2;
               bool simplified=A&&B;
               if(simplified!=unsimplified)
               equivalent=0;
              if(simplified==1&&unsimplified==simplified)
                 {v.push_back(A);
                 v.push_back(B);
                 v.push_back(C);}
     cout<<A<<"       "<<B<<"     "<<C<<"    "<<notC<<"       "<<BorC<<"       "<<AorC<<"          "<<exp1<<"         "<<BorNotC<<"      "<<AorNotC<<"         "<<exp2<<"                      "<<unsimplified<<"                        "<<simplified<<endl;
     
           } 
        }
    }
    cout<<"Equavalence: "<<equivalent<<endl;
    cout<<"Both expressions are satsifiable, The input values that make both expressions satisfiable are:"<<endl;
    cout<<"The input values for the unSimplified expression:"<<endl;
    cout<<"A"<<" "<<"B"<<" "<<"C";
    int count=2;
    while(count--){
        if(count==0)
        cout<<"The input values for the Simplified expression:" ;
    for(int i=0;i<v.size();i++){
        if((i%3)==0)
        cout<<endl;
     if(count==0&&(((i+1)%3)==0))
       cout<<"X"<<" ";
      else cout<<v[i]<<" ";

   
    }
    cout<<endl;
    }
   


    

}
