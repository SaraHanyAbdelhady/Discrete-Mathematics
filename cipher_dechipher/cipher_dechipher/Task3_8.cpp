#include <iostream>
#include <string>

using namespace std;

char Italian_Alphabet[21][2];

string Cipher(string msg) {
    char A = 'A';
    char a = 'a';
    // initializing Italian Alphabet
    for (int x = 0; x < 21; ++x) {
        if (A == 'J' || A == 'K' || A == 'W' || A == 'X' || A == 'Y') {
            A++;
            a++;
            x--;
            continue;
        }
        Italian_Alphabet[x][0] = a++;
        Italian_Alphabet[x][1] = A++;
    }
    string ciphered = "";
    int index;
    int capital;
    for (int i = 0; i < msg.size(); i++) {
        if (msg[i] == ' ') ciphered += msg[i];
        else {
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
            if (index == 21) return "the Text contains non italian letters, please enter another one containing italian letters only.";
            else {
                index = index * 5 + 2;
                index = index % 21;
                ciphered += Italian_Alphabet[index][capital];
            }
        }
    }
    return ciphered;
}

int main()
{
    string message = "COLPISCI IL NEMICO ORA";
    cout << Cipher(message);
}



