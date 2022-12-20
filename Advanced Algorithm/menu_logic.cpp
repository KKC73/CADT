#include <iostream>
#include "core_code.cpp"
using namespace std;

int zero_menu(){ // 0
    int choice;
    cout << "1. Sign in" << endl;
    cout << "2. Sign up" << endl;
    cout << "3. Exit" << endl;
    // old: cout << "Enter a number to choose: "; cin >> choice;
    choice = get_int_input(); // updated
    cout << "\n";
    if(choice == 1){
        return 1;
    } else if(choice == 2){
        return 2;
    } else if(choice == 3){
        exit(1);
    } else{
        return 0;
    }
}

int sign_in_menu(){ // 1
    int choice, priv;
    priv = privilege_status; // change_read_privilege_file(0, "read");
    cout << "Are you an admin or a user?" << endl;
    cout << "1. Admin" << endl;
    cout << "2. User" << endl;
    cout << "3. Go back" << endl;
    // old: cout << "Enter a number to choose: "; cin >> choice;
    choice = get_int_input(); // updated
    if(choice == 1){
        sign_in("admin");
        priv = privilege_status;
        // priv = change_read_privilege_file(0, "read");
        if(priv == 1){
            wait();
            return 3;
        } else{
            wait();
            return 1;
        }
    } else if(choice == 2){
        sign_in("user");
        priv = privilege_status;
        // priv = change_read_privilege_file(0, "read");
        if(priv == 0){
            cout << "User" << endl;
            // user page
            wait();
            return 6;
        } else{
            wait();
            return 1;
        }

    } else if(choice == 3){
        return 0;
    } else{
        return 1;
    }
}

int sign_up_menu(){ // 2
    int priv;
    cout << "Please, enter your username and password to sign up." << endl;
    new_user_prompt("user");
    priv = privilege_status;
    // priv = change_read_privilege_file(0, "read");
    if(priv == 0){
        cout << "User" << endl;
        // user page
        wait();
        return 6;
    } else{
        wait();
        return 2;
    }
}

int admin_menu(){ // 3
    int choice, priv;
    string username, password;
    cout << "What do you want to do?" << endl;
    cout << "1. CRUD operation on quizzes" << endl;
    cout << "2. Generate report" << endl;
    cout << "3. Add admin" << endl;
    cout << "4. Add user" << endl;
    cout << "5. Delete user" << endl;
    cout << "6. Sign out" << endl;
    // cout << "6. Go back" << endl;
    // Go back is not need bcuz this is already signed in used Sign out instead
    // old: cout << "Enter a number to choose: "; cin >> choice;
    choice = get_int_input(); // updated
    switch(choice){
    case 1:
        wait();
        return 4;
        break;
    case 2:
        // Generate report
        wait();
        return 5;
        break;
    case 3:
        // Add admin
        new_user_prompt("admin");
        wait();
        return 3;
        break;
    case 4:
        // Add user
        new_user_prompt("user");
        wait();
        return 3;
        break;
    case 5:
        // Delete user
        cout << "Enter a username to delete a user: ";
        cin >> username;
        delete_credential("user_credential.txt", username);
        wait();
        return 3;
        break;
    case 6:
        // Change privilege.txt to "havent decided" and go back to zero_menu()
        // priv = change_read_privilege_file(-1, "change");
        privilege_status = -1;
        cout << "\nSigning out..." << endl;
        wait();
        return 0;
        break;
    default:
        return 3; // Same page
        break;
    }
}

int CRUD_question_menu(){ // 4
    int choice;
    cout << "What operation do you want to do?" << endl;
    cout << "1. Add questions" << endl;
    cout << "2. Show questions" << endl;
    cout << "3. Remove questions" << endl;
    cout << "4. Update questions" << endl;
    cout << "5. Go back" << endl;
    // old: cout << "Enter a number to choose: "; cin >> choice;
    choice = get_int_input(); // updated
    cout << "\n";
    switch(choice){
    case 1:
        cout << "What subject do you want to add to?" << endl;
        subject_list();
        // old: cout << "Enter a number to choose: "; cin >> choice;
        choice = get_int_input(); // updated
        switch(choice){
        case 1:
            add_questions("math.txt");
            return 4;
            break;
        case 2:
            add_questions("physics.txt");
            return 4;
            break;
        case 3:
            add_questions("english.txt");
            return 4;
            break;
        case 4:
            return 4;
            break;
        default:
            return 4;
            break;
        }
    case 2:
        int q_num;
        cout << "What subject do you want to show?" << endl;
        subject_list(); cin >> choice;
        cout << "Enter 0 to show all questions" << endl;
        cout << "Enter the number of questions you want to show: ";
        // old: cin >> q_num;
        q_num = get_int_input(); // updated
        cout << "\n";
        switch(choice){
        case 1:
            show_questions("math.txt", q_num);
            wait();
            return 4;
            break;
        case 2:
            show_questions("physics.txt", q_num);
            wait();
            return 4;
            break;
        case 3:
            show_questions("english.txt", q_num);
            wait();
            return 4;
            break;
        case 4:
            return 4;
            break;
        default:
            return 4;
            break;
        }
    case 3:
        int ID;
        cout << "What subject do you want to remove questions from?" << endl;
        subject_list(); cin >> choice;
        cout << "\nEnter question ID: ";
        // old: cin >> ID;
        ID = get_int_input();
        cout << "\n";
        switch(choice){
        case 1:
            delete_q_by_ID("math.txt", ID);
            wait();
            return 4;
            break;
        case 2:
            delete_q_by_ID("physics.txt", ID);
            wait();
            return 4;
            break;
        case 3:
            delete_q_by_ID("english.txt", ID);
            wait();
            return 4;
            break;
        case 4:
            return 4;
            break;
        default:
            return 4;
            break;
        }
    case 4:
        // Update questions
        cout << "What subject do you want to update questions?" << endl;
        subject_list(); cin >> choice;
        cout << "\nEnter question ID: ";
        // old: cin >> ID;
        ID = get_int_input();
        cout << "\n";
        switch(choice){
        case 1:
            update_quizz("math.txt", ID);
            wait();
            return 4;
            break;
        case 2:
            update_quizz("physics.txt", ID);
            wait();
            return 4;
            break;
        case 3:
            update_quizz("english.txt", ID);
            wait();
            return 4;
            break;
        case 4:
            return 4;
            break;
        default:
            return 4;
            break;
        }
        return 4;
    case 5:
        // Go Back
        return 3;
    default:
        return 4;
    }
}

int generate_report_menu(){ // 5
    int choice;

    cout << "What report do you want to generate?" << endl;
    cout << "1. Average point report" << endl;
    cout << "2. Attendance report" << endl;
    cout << "3. Report on individuals" << endl;
    cout << "4. Go back" << endl;
    choice = get_int_input();

    switch(choice){
    case 1:
        generate_report();
        print_out_report();
        return 5;
        break;
    case 2:
        under_maintainance_prompt();
        return 5;
        break;
    case 3:
        under_maintainance_prompt();
        return 5;
        break;
    case 4:
        under_maintainance_prompt();
        return 3;
        break;
    default:
        return 5;
        break;
    }

}

/*
int generate_report_menu(){ // 5
    int choice;
    string line;
    string * cred;
    cout << "What report do you want to generate?" << endl;
    cout << "1. Average point report" << endl;
    cout << "2. Attendance report" << endl;
    cout << "3. Report on individuals" << endl;
    cout << "4. Go back" << endl;
    choice = get_int_input();
    wait();
    if(choice == 1){
        //
        cout << "choice: " << choice << endl;
        cout << "choice == 1: " << choice == 1 << endl;

        return 5;
    } else if(choice == 2){
        cout << "Under Maintainance" << endl;
        return 5;
    } else if(choice == 3){
        cout << "Under Maintainance" << endl;
        return 5;
    } else if(choice == 4){
        cout << "Under Maintainance" << endl;
        return 3;
    } else{
        return 5;
    }
}
*/

int user_menu(){ // 6
    int choice, priv;
    string username, password;
    cout << "What do you want to do?" << endl;
    cout << "1. Take a quiz" << endl;
    cout << "2. Check my profile" << endl;
    cout << "3. Check leaderboard" << endl;
    cout << "4. Change password" << endl;
    cout << "5. Sign out" << endl;
    choice = get_int_input();
    switch(choice){
    case 1:
        wait();
        return 7;
        break;
    case 2:
        under_maintainance_prompt();
        return 6;
        // return 8;
        break;
    case 3:
        under_maintainance_prompt();
        return 6;
        // return 9;
        break;
    case 4:
        under_maintainance_prompt();
        return 6;
        // return 10;
    case 5:
        cout << "\nSigning out..." << endl;
        wait();
        return 0;
        break;
    default:
        return 6;
        break;
    }
}

int take_a_quiz_menu(){ // 7
    int choice;
    cout << "I see you want to take a quiz!" << endl;
    cout << "Please, choose a subject: " << endl;
    subject_list();
    choice = get_int_input();
    wait();
    system("clear");
    switch(choice){
    case 1:
        // Take a math quiz
        take_a_quiz("math.txt");
        wait();
        return 7;
        break;
    case 2:
        // Take a physics quiz
        take_a_quiz("physics.txt");
        wait();
        return 7;
        break;
    case 3:
        // Take a english quiz
        take_a_quiz("english.txt");
        wait();
        return 7;
        break;
    case 4:
        return 6;
        break;
    default:
        return 7; // Same page
        break;
    }
}

int check_user_profile(){ // 8
    cout << "You are logged in as: " << logged_in_as << endl;
    cout << "Your average score is: " << cal_avg_username(logged_in_as) << endl;
    // Attandance
    // Average Point
    // Highest Point
    // Lowest Point
    wait();
    return 6;
    // Show username, attandance, average point, highest point, lowest point
}

int check_leaderboard(){ // 9
    // Show by point or attandance
}

int change_user_password(){ // 10
    // change user password
}

