#include <iostream>
#include <string>

using namespace std;

char Italian_Alphabet[21][2];

string Cipher(string msg) {
    char A = 'A';   
    char a = 'a';
    // initializing Italian Alphabet
    for (int x = 0; x < 21; ++x) {
        if (A == 'J' || A == 'K' || A == 'W' || A == 'X' || A == 'Y') // excluded for Italian Alphabets
        {
            A++;
            a++;
            x--;
            continue;
        }
        Italian_Alphabet[x][0] = a++;   // small letters
        Italian_Alphabet[x][1] = A++;   // capital letters
    }
    string ciphered = "";
    int index;
    int capital;
    for (int i = 0; i < msg.size(); i++) {
        index = 0;
        if (msg[i] == ' ') ciphered += msg[i]; // preserve spaces
        else {
            //removing grave and acute accents À à È è É é Ì ì Ò ò Ó ó Ù ù
            if (msg[i] == 'À') msg[i] = 'A';
            else if (msg[i] == 'à') msg[i] = 'a';
            else if (msg[i] == 'È' || msg[i] == 'É') msg[i] = 'E';
            else if (msg[i] == 'è' || msg[i] == 'é') msg[i] = 'e';
            else if (msg[i] == 'Ì') msg[i] = 'I';
            else if (msg[i] == 'ì') msg[i] = 'i';
            else if (msg[i] == 'Ò' || msg[i] == 'Ó') msg[i] = 'O';
            else if (msg[i] == 'ò' || msg[i] == 'ó') msg[i] = 'o';
            else if (msg[i] == 'Ù') msg[i] = 'U';
            else if (msg[i] == 'ù') msg[i] = 'u';
            for (index = 0; index < 21; index++) {
                if (msg[i] == Italian_Alphabet[index][0]) {
                    capital = 0;
                    break;
                }
                else if(msg[i] == Italian_Alphabet[index][1]) {
                    capital = 1;
                    break;
                }
            }
            if (index == 21) //if not a italian letter
                return "the Text contains non italian letters, please enter another one containing italian letters only.";
            else {
                // applying cipher equation
                index = index * 5 + 2;
                index = index % 21;
                ciphered += Italian_Alphabet[index][capital]; // adding ciphered letters
            }
        }
    }
    return ciphered;
}

int main()
{
    string message = "COLPISCI IL NEMICO ORA";
    cout << Cipher(message) << endl;
    string message2;
    getline(cin, message2);
    cout << Cipher(message2);
}



