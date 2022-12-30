#include <iostream>
#include <string>
#include <conio.h>
using namespace std;
string star_password(){
   string pass ="";
   char ch;
   ch = _getch();
   while(ch != 13){//character 13 is enter
      pass.push_back(ch);
      cout << '*';
      ch = _getch();
   }
   return pass;
}

main(){
    string hi = star_password();
    cout << "hello: " << hi;
}
