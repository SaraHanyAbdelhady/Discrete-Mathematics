#include<iostream>

using namespace std;

int main(){
    string p1,p2,con;
    cout<<"Please enter premises 1"<<"\n";
    cin>>p1;
    cout<<"Please enter premises 2"<<"\n";
    cin>>p2;
    cout<<"Please enter the conclusion"<<"\n";
    cin>>con;
    bool c,a,h;
    bool satisfiable = 0;
    bool valid = 0;
    int counter1=0,counter2=0;
    bool C,A,H;
     cout<<"C"<<"       "<<"A"<<"     "<<"H"<<"    "<<"~H"<<"     "<<"~C"<<"      "<<"premises1"<<"       "<<"premises2"<<"       "<<"conclusion"<<endl;
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
                   counter1++;
                  if(conclusion) counter2++;
               } 
            
               cout<<C<<"       "<<A<<"     "<<H<<"     "<<notH<<"      "<<notC<<"        "<<premises1<<"                "<<premises2<<"               "<<conclusion<<endl;
           } 
        }
    }
    if(counter1==counter2)
    valid=1;
    cout<<"Satisfiable: "<<satisfiable<<" Valid: "<<valid<<endl;
}
