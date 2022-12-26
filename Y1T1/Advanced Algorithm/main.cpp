#include <iostream>
#include <fstream>
//#include "my_lib.cpp"
#include "menu_logic.cpp"
using namespace std;
main(){
    //new_user_prompt("admin");
    //new_user_prompt("user");
    //sign_in("user");

    loarding_bar("Loading...");

    cout << "\t\t*************************" << endl;
    cout << "\t\t*   Welcome to Quiz B   *" << endl;
    cout << "\t\t*************************" << endl << endl;

    int nav;
    nav = 0;
    while(1==1){
        switch(nav){
        case 0:
            nav = zero_menu();
            system("clear");
            break;
        case 1:
            nav = sign_in_menu();
            system("clear");
            break;
        case 2:
            nav = sign_up_menu();
            system("clear");
            break;
        case 3:
            loarding_bar("Loading...");
            nav = admin_menu();
            system("clear");
            break;
        case 4:
            nav = CRUD_question_menu();
            system("clear");
            break;
        case 5:
            nav = generate_report_menu();
            system("clear");
            generate_report();
            system("clear");
            break;
        case 6:
            loarding_bar("Loading...");
            nav = user_menu();
            system("clear");
            break;
        case 7:
            nav = take_a_quiz_menu();
            system("clear");
            break;
        case 8:
            nav = check_user_profile();
            system("clear");
            break;
        case 9:
            nav = check_leaderboard();
            system("clear");
            break;
        case 10:
            nav = change_user_password();
            system("clear");
            break;
        default:
            break;
        }
        cout << "\n";
    }
}

