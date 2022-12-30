#include <iostream>
using namespace std;

string encrypt(string text, int s = 3){
    string result = "";

    for (int i = 0; i < text.length(); i++) {
        result += char(int(text[i] + s));
    }
    return result;
}

string decrypt(string text, int s = 3){
    string result = "";

    for (int i = 0; i < text.length(); i++) {
        result += char(int(text[i] - s));
    }
    return result;
}

