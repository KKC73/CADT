#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <limits>
#include <time.h>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <conio.h>
#include "MyQueue.cpp"
#include "caesar_cipher.cpp"
//#include "file_op.cpp"
string logged_in_as = "ab";
int privilege_status;
int real_case_q_num = 5;

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

void loarding_bar(string caption){
  int i;
  cout << "\n\t\t\t" << caption << "\n\t\t";
  for(i=0;i<26;i++){
    cout << char(178);
  }
  cout << "\r\t\t";
  for(i=26;i>0;i--){
    cout << char(219);
    this_thread::sleep_for(chrono::milliseconds(40));
  }
  system("clear");
}

void tabs(){
    cout << "\t\t\t";
}

void wait(){ // press ENTER key to continue the program
    cin.get();
    do{
        cout << "\n\t\tPress ENTER key to continue...";
    } while(cin.get() != '\n');
}

void under_maintainance_prompt(){
    system("clear");
    cout << "\n\t\t      Under Maintainance :(\n" << endl;
    wait();
}

int get_space_count(string line){
    int space_count = 0;
    for(int i=0; i<line.length(); i++){
        if(isspace(line[i])){
            space_count++;
        }
    }
    return space_count;
}

int get_int_input(int masked = 0){ // get integer only input
    int x;
    if(masked == 0){
        cout << "\n\t\tEnter a choice: ";
    }
     cin >> x;

    // Using infinite loop for input validation
    while(1){
        if(cin.fail()) // Returns true when input fails
        {
            cin.clear(); // Use to clear error state of buffer

            // Ignores rest of the line
            // After first error occurs

            // Skips to the next line
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "\n\t\tPlease enter a valid input: ";
            cin >> x ;

        }
        if(!cin.fail())
        break;

    }
    return x;

}

int file_exists(string file_path){
    ifstream file;
    file.open(file_path);
    if (file){
        return 1;
    }
    else{
        return 0;
    }
}

int get_num_of_q(string quiz_name){ // Get number of a quiz's number of question
    fstream quiz;
    quiz.open(quiz_name, ios::in);
    string line;
    int num_of_q = 0;
    while(getline(quiz, line)){
        num_of_q++;
    }
    quiz.close();
    return num_of_q/6;
}

void subject_list(){
    cout << "\t\t1. Mathematics" << endl;
    cout << "\t\t2. Physics" << endl;
    cout << "\t\t3. English" << endl;
    cout << "\t\t4. Go back" << endl;
}

void add_user(string file_path, string name, string password){ // add user credential
    fstream file;
    file.open(file_path, ios::app);
    file << name;
    file << " ";
    file << password;
    file << "\n";
    file.close();
}

string * split_by_space(string str, int num_space){ // Split a string by space and return array credential[num_space] | credential[0] is specific for working with credential
    num_space += 2;
    string * credential = new string[num_space];
    credential[0] = "0";
    int i;
    istringstream ss(str);
    string word;
    i = 1;
    while (ss >> word){
        credential[i] = word;
        i++;
    }
    return credential;
}

string * username_exists(string username, string file_path){ // Fild username in file_path | return array credential, which credential[0] is the status of being found
    string * credential;
    string line;
    fstream file;
    file.open(file_path, ios::in);
    while(getline(file, line)){
        credential = split_by_space(line, get_space_count(line));
        if(credential[1].compare(username) == 0){
            credential[0] = "1";
            return credential;
        }
    }
    file.close();
    credential = split_by_space(line, get_space_count(line));
    credential[0] = "0";
    return credential;
}

void new_user_prompt(string privilege){ // privilege is either user or admin
    string username, password, re_password;
    string * credential;
    cout << "\t\tEnter a new username: "; cin >> username;
    cout << "\n\t\tEnter 'q' to quit...\n";
    do{
        cout << "\t\tEnter a new password: "; password = star_password();
        cout << endl;
        if(password.compare("q") == 0){
            return;
        }
        cout << "\t\tRe-enter the password: "; re_password = star_password();
        if(re_password.compare("q") == 0){
            return;
        }
        cout << endl << endl;
    } while(password.compare(re_password));

    password = encrypt(password);
    if(privilege.compare("admin") == 0){
        credential = username_exists(username, "admin_credential.txt");
        if(credential[0].compare("0") == 0){
            add_user("admin_credential.txt", username, password);
            cout << "\n\t\tAdmin has been added..." << endl;
            privilege_status = 1;
            // change_read_privilege_file(1, "change");
        } else{
            cout << "\n\t\tUsername has already been taken..." << endl;
            privilege_status = -1;
            // change_read_privilege_file(-1, "change"); // Failure of admin log in
        }
    }else {
        credential = username_exists(username, "user_credential.txt");
        if(credential[0].compare("0")  == 0){
            add_user("user_credential.txt", username, password);
            privilege_status = 0;
            cout << "\n\t\tUser has been added..." << endl;
            // change_read_privilege_file(0, "change");
            logged_in_as = username;
        } else{
            cout << "\n\t\tUsername has already been taken..." << endl;
            privilege_status = -2;
            // change_read_privilege_file(-2, "change"); // Failure of user log in
        }
    }
}

void sign_in(string privilege){
    // Successful sign in: privilege.txt holds 1 for admin, 0 for user
    // Failed sign in: privilege.txt holds -1
    string username, password, re_password;
    string * credential;
    cout << "\t\tEnter your username: "; cin >> username;
    cout << "\n\t\tEnter 'q' to quit...\n";
    do{
        cout << "\t\tEnter a new password: "; password = star_password();
        cout << endl;
        if(password.compare("q") == 0){
            return;
        }
        cout << "\t\tRe-enter the password: "; re_password = star_password();
        if(re_password.compare("q") == 0){
            return;
        }
        cout << endl << endl;
    } while(password.compare(re_password));
    if(privilege.compare("admin") == 0){
        credential = username_exists(username, "admin_credential.txt");
        credential[2] = decrypt(credential[2]);
        if(credential[0].compare("1")  == 0 && credential[2].compare(password) == 0){
            logged_in_as = credential[1];
            privilege_status = 1;
            // change_read_privilege_file(1, "change");
        } else {
            cout << "\n\t\tSign in is not successful!" << endl;
            privilege_status = -1;
            // change_read_privilege_file(-1, "change"); // Failure of admin log in
        }
    }else {
        credential = username_exists(username, "user_credential.txt");
        credential[2] = decrypt(credential[2]);
        if(credential[0].compare("1")  == 0 && credential[2].compare(password) == 0){
            cout << "\n\t\tWelcome, " << credential[1] << "!" << endl;
            logged_in_as = credential[1];
            privilege_status = 0;
            // change_read_privilege_file(0, "change");
        } else {
            cout << "\n\t\tSign in is not successful!" << endl;
            privilege_status = -2;
            // change_read_privilege_file(-2, "change"); // Failure of user log in
        }
    }
}

void delete_credential(string file_path, string username){ // Removal of a user or an admin by an admin
    string sure = "n";

    cout << "\n\t\t\nAre you sure?(Y/N) "; cin >> sure;
    cout << "\n";

    if(!sure.compare("N") || !sure.compare("n")){
        return;
    }

    string * credential;
    credential = username_exists(username, "user_credential.txt");
    if(credential[0].compare("0") == 0){
        cout << "\n\t\tUser doesn't exist." << endl;
    } else{
        int n = file_path.length();

        // declaring character array
        char file_path_char[n + 1];

        // copying the contents of the
        // string to char array
        strcpy(file_path_char, file_path.c_str());

        string deleteline;
        string line;

        fstream original;
        original.open(file_path_char, ios::in);
        fstream temp;
        temp.open("temp.txt", ios::out);

        string * credential;

        while(getline(original, line)){
            credential = split_by_space(line, get_space_count(line));
            if(credential[1].compare(username) == 0){
                continue;
            } else{
                temp << line;
                temp << "\n";
            }
        }

        temp.close();
        original.close();
        remove(file_path_char);
        rename("temp.txt", file_path_char);
        cout << "\n\t\tUser has been deleted." << endl;
    }
}

void add_questions(string quiz_name){ // Add question to quiz_name
    fstream quiz;
    quiz.open(quiz_name, ios::app);
    int q_num;
    string input_text;
    cout << "\n\t\tYou are adding question(s) to " << quiz_name << endl;
    cout << "\t\tEnter the number of questions: "; cin >> q_num;
    cout << "\n";
    getline(cin, input_text);
    for(int i=0; i<q_num; i++){
        for(int j=0; j<6; j++){
            switch(j){
            case 0:
                cout << "\t\tEnter question number " << i + 1 << ": ";
                getline(cin, input_text);
                quiz << input_text << "\n";
                break;
            case 1:
                cout << "\t\tEnter answer A: ";
                getline(cin, input_text);
                quiz << input_text << "\n";
                break;
            case 2:
                cout << "\t\tEnter answer B: ";
                getline(cin, input_text);
                quiz << input_text << "\n";
                break;
            case 3:
                cout << "\t\tEnter answer C: ";
                getline(cin, input_text);
                quiz << input_text << "\n";
                break;
            case 4:
                cout << "\t\tEnter answer D: ";
                getline(cin, input_text);
                quiz << input_text << "\n";
                break;
            case 5:
                cout << "\t\tEnter the correct answer: ";
                getline(cin, input_text);
                quiz << input_text << "\n";
                break;
            default:
                break;
            }
        }

    }
    quiz.close();
}

void show_questions(string quiz_name, int num_of_q){ // num_of_q = 0 print all
    if(!file_exists(quiz_name)){
        cout << "\n\t\t" << quiz_name << " has no questions yet" << endl;
    } else{
        fstream quiz;
        quiz.open(quiz_name, ios::in);
//      int q_num;
//      string input_text;
//      cout << "Enter the number of questions: "; cin >> q_num;
        string line;
        int cur_line = 0;
        while(getline(quiz, line)){
            cur_line++;
            switch(cur_line%6){
                case 1:
                    cout << "\t\tQuestion ID: " << cur_line/6 + 1 << ": ";
                    cout << line << endl;
                    break;
                case 2:
                    cout << "\t\tA. ";
                    cout << line << endl;
                    break;
                case 3:
                    cout << "\t\tB. ";
                    cout << line << endl;
                    break;
                case 4:
                    cout << "\t\tC. ";
                    cout << line << endl;
                    break;
                case 5:
                    cout << "\t\tD. ";
                    cout << line << endl;
                    break;
                case 6:
                    cout << "\t\tCorrect answer: ";
                    cout << line << endl;
                    break;
                default:
                    break;
            }
            if(cur_line/6 == num_of_q && cur_line/6 != 0){
                cout << cur_line;
                break;
            }
        }
        quiz.close();
    }

}

void delete_q_by_ID(string quiz_name_ori, int ID){
    // Delete q by ID
    string sure = "no";
    cout << "\t\t\nAre you sure?(Y/N) "; cin >> sure;
    cout << "\n";

    if(!sure.compare("N") || !sure.compare("n")){
        return;
    }

    if(ID > get_num_of_q(quiz_name_ori)){
        cout << "\n\t\tID out of bound..." << endl;
        cout << "\t\tMaximum ID is " << get_num_of_q(quiz_name_ori) << endl;
        return;
    }

    int n = quiz_name_ori.length();

    // declaring character array
    char quiz_name[n + 1];

    // copying the contents of the
    // string to char array
    strcpy(quiz_name, quiz_name_ori.c_str());

    fstream original;
    original.open(quiz_name, ios::in);
    fstream temp;
    temp.open("temp.txt", ios::out);

    string line;
    int cur_line = 0;

    while(getline(original, line)){
        // (ID-1)*6  < cur_line <= ID*6
        // cur_line > (ID-1)^6 && cur_line <= ID*6
        cur_line++;
        if(cur_line > (ID-1)*6 && cur_line <= ID*6){
            continue;
        } else{
            temp << line;
            temp << "\n";
        }
    }

    temp.close();
    original.close();
    remove(quiz_name);
    rename("temp.txt", quiz_name);
    cout << "\n\t\tQuestion has been deleted." << endl;
}

void update_quizz(string quiz_name_ori, int ID){
    // Delete q by ID

    if(ID > get_num_of_q(quiz_name_ori)){
        cout << "\n\t\tID out of bound..." << endl;
        cout << "\t\tMaximum ID is " << get_num_of_q(quiz_name_ori) << endl;
        return;
    }

    int n = quiz_name_ori.length();

    // declaring character array
    char quiz_name[n + 1];

    // copying the contents of the
    // string to char array
    strcpy(quiz_name, quiz_name_ori.c_str());

    fstream original;
    original.open(quiz_name, ios::in);
    fstream temp;
    temp.open("temp.txt", ios::out);

    string line;
    string new_status;
    int cur_line = 0;

    while(getline(original, line)){
        // (ID-1)*6  < cur_line <= ID*6
        // cur_line > (ID-1)^6 && cur_line <= ID*6
        cur_line++;
        if(cur_line > (ID-1)*6 && cur_line <= ID*6){
            switch(cur_line%6){
                case 1:
                    cout << "\t\tQuestion number " << cur_line/6 + 1 << "\n";
                    cout << "\n\t\tCurrent question: " << line << endl;
                    cout << "\t\tNew question: "; cin >> new_status;
                    cout << "\n";
                    temp << new_status;
                    temp << "\n";
                    break;
                case 2:
                    cout << "\t\tCurrent answer A: ";
                    cout << line << endl;
                    cout << "\t\tNew answer: "; cin >> new_status;
                    cout << "\n";
                    temp << new_status;
                    temp << "\n";
                    break;
                case 3:
                    cout << "\t\tCurrent answer B: ";
                    cout << line << endl;
                    cout << "\t\tNew answer: "; cin >> new_status;
                    cout << "\n";
                    temp << new_status;
                    temp << "\n";
                    break;
                case 4:
                    cout << "\t\tCurrent answer C: ";
                    cout << line << endl;
                    cout << "\t\tNew answer: "; cin >> new_status;
                    cout << "\n";
                    temp << new_status;
                    temp << "\n";
                    break;
                case 5:
                    cout << "\t\tCurrent answer D: ";
                    cout << line << endl;
                    cout << "\t\tNew answer: "; cin >> new_status;
                    cout << "\n";
                    temp << new_status;
                    temp << "\n";
                    break;
                case 0:
                    cout << "\t\tCurrent correct answer: ";
                    cout << line << endl;
                    cout << "\t\tNew correct answer: "; cin >> new_status;
                    cout << "\n";
                    temp << new_status;
                    temp << "\n";
                    break;
                default:
                    break;
            }
        } else{
            temp << line;
            temp << "\n";
        }
    }

    temp.close();
    original.close();
    remove(quiz_name);
    rename("temp.txt", quiz_name);
    cout << "\n\t\tQuestion has been updated." << endl;
}


int is_element_in_arr(int arr[], int q_num, int toSearch){
    int i, found;
    found = 0;
    for(i=0; i<q_num; i++){
        if(arr[i] == toSearch)
        {
            found = 1;
            break;
        }
    }
    return found;
}

int * randomize_ID(int q_num, int real_case_q_num){

	// Providing a seed value
	srand((unsigned) time(NULL));
	// string * credential = new string[num_space];
	int * num = new int[real_case_q_num];
	for(int i=0; i<real_case_q_num; i++){
        num[i] = 0;
	}
	int i = 0;
	while(1){
        int random_num = (rand() % q_num) + 1;
        if(!is_element_in_arr(num, real_case_q_num, random_num)){
            num[i] = random_num;
            i++;
        }
        if(i == real_case_q_num){
            break;
        }

	}
	return num;
}

void add_q_to_queue(MyQueue * q_queue, string quiz_name_ori, int ID){
    if(ID > get_num_of_q(quiz_name_ori)){
        cout << "\n\t\tID out of bound..." << endl;
        cout << "\t\tMaximum ID is " << get_num_of_q(quiz_name_ori) << endl;
        return;
    }

    int n = quiz_name_ori.length();

    // declaring character array
    char quiz_name[n + 1];

    // copying the contents of the
    // string to char array
    strcpy(quiz_name, quiz_name_ori.c_str());

    fstream original;
    original.open(quiz_name, ios::in);

    string line;
    int cur_line = 0;

    while(getline(original, line)){
        // (ID-1)*6  < cur_line <= ID*6
        // cur_line > (ID-1)^6 && cur_line <= ID*6
        cur_line++;
        if(cur_line > (ID-1)*6 && cur_line <= ID*6){
            enqueue(q_queue, line);
        }
    }
    original.close();
}

int * randomize_q(){
    int limit = 4;

    srand((unsigned) time(NULL));
	// string * credential = new string[num_space];
	int * num = new int[limit];
	for(int i=0; i<limit; i++){
        num[i] = 0;
	}
	int i = 0;
	while(1){
        int random_num = (rand() % 4) + 1;
        if(!is_element_in_arr(num, limit, random_num)){
            num[i] = random_num;
            i++;
        }
        if(i == limit){
            break;
        }

	}

	for(int i=0; i<4; i++){
        num[i] = num[i] - 1;
    }

	return num;
}

int is_element_in_num_arr(int arr[], int toSearch){
    int i;
    for(i=0; i<4; i++){
        if(arr[i] == toSearch)
        {
             return i;
        }
    }
}

void take_a_quiz(string quiz_name){

    int cancel = 0, num_of_cor = 0;

    ifstream QNum;
    QNum.open("QNum.txt");
    if(QNum){
        QNum >> real_case_q_num;
        QNum.close();
    }

    MyQueue *my_queue = createEmptyQueue();
    int q_num = get_num_of_q(quiz_name);
    ifstream file;
    file.open(quiz_name);
    if(file){
        if(q_num > 0){
            file.close();
        } else{
            cout << "\t\t" << quiz_name << " has no questions yet!" << endl;
            return;
        }
    } else{
        cout << "\t\t" << quiz_name << " has no questions yet!" << endl;
        return;
    }

    string line;

    double score = 0;

    string user_ans, cor_ans;


    fstream quiz_file;

    if(q_num >= real_case_q_num){
            real_case_q_num = real_case_q_num;
        } else{
            real_case_q_num = q_num;
        }

    int * random_ID;
    random_ID = randomize_ID(q_num, real_case_q_num);

    for(int i=0; i<real_case_q_num; i++){ // Loop through question
        add_q_to_queue(my_queue, quiz_name, random_ID[i]);
    }

    string answer_list[4];
    int *num;
    num = randomize_q();
    int order_track[4];

    for(int k=0; k<real_case_q_num; k++){
        num = randomize_q();
        for(int i=1; i<=5; i++){

            if(i == 1){
                cout << "\t\t\tQuestion " << k + 1 << endl;
                cout << "\t\tID-"<< random_ID[k] << ": " << dequeue(my_queue) << endl;
            } else{
                order_track[num[i-2]] = i-2;
                answer_list[num[i-2]] = dequeue(my_queue);
            }

//            switch(i){
//            case 1:
//                cout << "\t\t\tQuestion " << k + 1 << endl;
//                cout << "\t\tID-"<< random_ID[k] << ": " << dequeue(my_queue) << endl;
//                break;
//            default:
//                transform(cor_ans.begin(), cor_ans.end(), cor_ans.begin(), ::toupper);
//                answer_list[integer_sequence[i-1]] = dequeue(my_queue);
//                cout << answer_list[i-1] << " " << integer_sequence[i-1] << endl;
//                break;
//            case 2:
//                cout << "\t\tA. " << ": " << dequeue(my_queue) << endl;
//                break;
//            case 3:
//                cout << "\t\tB. " << ": " << dequeue(my_queue) << endl;
//                break;
//            case 4:
//                cout << "\t\tC. " << ": " << dequeue(my_queue) << endl;
//                break;
//            case 5:
//                cout << "\t\tD. " << ": " << dequeue(my_queue) << endl;
//                break;
//            default:
//                break;
//
//            }
        }

        for(int i = 0; i<4; i++){
            cout << "\t\t" << char(65+i) << ". " << answer_list[i] << endl;
        }

        cout << "\n\t\t***Enter \"s\" to skip (You can't come back)***" << endl;
        cout << "\t\t***Enter \"q\" to cancel***\n" << endl;
        do{
            cout << "\t\tEnter your answer: "; cin >> user_ans;

        } while(!((user_ans[0] >= 'A' && user_ans[0] <= 'D') || (user_ans[0] >= 'a' && user_ans[0] <= 'd')));
        cor_ans = dequeue(my_queue);

        transform(cor_ans.begin(), cor_ans.end(), cor_ans.begin(), ::toupper);

        cor_ans[0] = char(is_element_in_num_arr(order_track, cor_ans[0] - 65) + 65);

        //is_element_in_arr(num, 4, int)
        //cor_ans = ;
        transform(user_ans.begin(), user_ans.end(), user_ans.begin(), ::toupper);

        if(!user_ans.compare(cor_ans)){
            cout << "\n\t\tCorrect answer: " << cor_ans << endl;
            cout << "\t\tYour answer: " << user_ans << endl << endl;
            cout << "\t\tYou got it :)" << endl;
            num_of_cor++;
            score++;
        } else if(!user_ans.compare("S") || !user_ans.compare("SKIP")){
            cout << "\n\t\tCorrect answer: " << cor_ans << endl;
            score += 0;
        } else if(!user_ans.compare("Q") || !user_ans.compare("QUIT")){
            cancel = 1;
            system("clear");
            break;
        } else{
            cout << "\n\t\tCorrect answer: " << cor_ans << endl;
            cout << "\t\tYour answer: " << user_ans << endl << endl;
            cout << "\t\tSorry, you didn't get it :(" << endl;
            if(score > 0){
                score -= 0.5;
            }
        }
        wait();
        system("clear");
    }

    if(cancel == 0){
        cout << "\n\n\t\tYou got " << num_of_cor << " out of " << real_case_q_num << " question(s) right" << endl;
        cout << "\t\tYour score is " << score << endl;
        fstream score_record;
        score_record.open("score_record.txt", ios::app);
        score_record << logged_in_as << " " << quiz_name << " " << score << endl;
        score_record.close();
    }


}

double cal_avg_username(string username){
    string file_path = "score_record.txt";
    int num_of_entries = 0;
    double sum = 0;
    string line;
    string *record_line;
    fstream score_record;
    score_record.open(file_path, ios::in);
    while(getline(score_record, line)){
        record_line = split_by_space(line, get_space_count(line) + 1);
        if(!record_line[1].compare(username)){
            record_line = split_by_space(line, get_space_count(line));
            sum += stod(record_line[3]);
            num_of_entries++;
        }
    }
    score_record.close();
    if(num_of_entries == 0){
        return 0;
    }
    return sum/num_of_entries;
}

void sort_score_report(MyQueue *avg_record_queue, MyQueue *sorted_avg, string file_path){

    string line, entry;
    double cur_max;
    fstream avg_record;
    avg_record.open(file_path, ios::in);
    while(getline(avg_record, line)){
        enqueue(avg_record_queue, line);
    }

    string * user_avg;

    for(int i=0; i<avg_record_queue->n; i++){
        cur_max = -1;
        Element *tmp;
        tmp = avg_record_queue->front;
        while(tmp!=NULL){
            user_avg = split_by_space(tmp->data, get_space_count(tmp->data));
            if(cur_max < stod(user_avg[2]) && !isDataIn(sorted_avg, tmp->data)){
                cur_max = stod(user_avg[2]);
                entry = tmp->data;
            } else if(cur_max == stod(user_avg[2]) && !isDataIn(sorted_avg, tmp->data)){
                if(!(entry.compare(tmp->data) < 0)){
                    cur_max = stod(user_avg[2]);
                    entry = tmp->data;
                }
            }
            tmp = tmp->next;
        }
        if(isDataIn(sorted_avg, entry)){
            //cout << "DUP: " << entry << endl;
            continue;
        } else{
            //cout << "NOT DUP: " << entry << endl;
            enqueue(sorted_avg, entry);
        }
    }

    avg_record.close();
}
void generate_report(){

    string line;
    string * cred;

    fstream user;
    user.open("user_credential.txt", ios::in);
    fstream avg_record;
    avg_record.open("avg_record.txt", ios::app);
    while(getline(user, line)){
        cred = split_by_space(line, get_space_count(line));
        avg_record << cred[1] << " " << cal_avg_username(cred[1]) << endl;
    }
    user.close();
    avg_record.close();
}

void print_out_report(){

    system("clear");

    MyQueue *avg_record_queue = createEmptyQueue();
    MyQueue *sorted_avg = createEmptyQueue();

    sort_score_report(avg_record_queue, sorted_avg, "avg_record.txt");

    int setw_value = 20;
    string * user_avg;

    cout << "\n\t\t    Average score report" << endl;
    cout << "\t\t    ====================\n" << endl;
    cout << "\t\t" << setw(setw_value) << left << "Username" << setw(setw_value) << left << "Average Score" << endl;

    fstream avg_record_write;
    avg_record_write.open("avg_record.txt", ios::out);
    Element *tmp;
    tmp = sorted_avg->front;
    while(tmp!=NULL){
        user_avg = split_by_space(tmp->data, get_space_count(tmp->data));
        cout << "\t\t" << setw(setw_value) << left << user_avg[1] << setw(setw_value) << left << user_avg[2] << endl;
        avg_record_write << tmp->data << endl;
        tmp = tmp->next;
    }
    avg_record_write.close();
    wait();
}

void sort_attendance_report(string file_path){

    MyQueue *attendance_queue = createEmptyQueue();
    MyQueue *sorted_attendance_q = createEmptyQueue();

    string line, entry;
    int cur_max;
    fstream attendance_read;
    attendance_read.open(file_path, ios::in);
    while(getline(attendance_read, line)){
        enqueue(attendance_queue, line);
    }

    string * user_avg;

    for(int i=0; i<attendance_queue->n; i++){
        cur_max = -1;
        Element *tmp;
        tmp = attendance_queue->front;
        while(tmp!=NULL){
            user_avg = split_by_space(tmp->data, get_space_count(tmp->data));
            if(cur_max < stoi(user_avg[2]) && !isDataIn(sorted_attendance_q, tmp->data)){
                cur_max = stoi(user_avg[2]);
                entry = tmp->data;
            } else if(cur_max == stoi(user_avg[2]) && !isDataIn(sorted_attendance_q, tmp->data)){
                if(!(entry.compare(tmp->data) < 0)){
                    cur_max = stoi(user_avg[2]);
                    entry = tmp->data;
                }
            }
            tmp = tmp->next;
        }
        if(isDataIn(sorted_attendance_q, entry)){
            //cout << "DUP: " << entry << endl;
            continue;
        } else{
            //cout << "NOT DUP: " << entry << endl;
            enqueue(sorted_attendance_q, entry);
        }
    }

    attendance_read.close();

    fstream attendance_write;
    attendance_write.open(file_path, ios::out);

    Element *tmp;
    tmp = sorted_attendance_q->front;
    while(tmp!=NULL){
        user_avg = split_by_space(tmp->data, get_space_count(tmp->data));
        attendance_write << tmp->data << endl;
        tmp = tmp->next;
    }

    attendance_write.close();

}

void record_attendance(){

    string * attendance_line;
    string * user_status;
    string line;

    fstream attendance_read;
    attendance_read.open("attendance.txt", ios::in);

    fstream attendance_write;
    attendance_write.open("tmp.txt", ios::app);

    user_status = username_exists(logged_in_as, "attendance.txt");

    if(!stoi(user_status[0])){
        while(getline(attendance_read, line)){
            attendance_line = split_by_space(line, get_space_count(line));
            attendance_write << attendance_line[1] << " " << stoi(attendance_line[2]) << endl;
        }
        attendance_write << logged_in_as << " " << "1" << endl;
    } else{
        while(getline(attendance_read, line)){
            attendance_line = split_by_space(line, get_space_count(line));
            if(attendance_line[1] == logged_in_as){
                attendance_write << logged_in_as << " " << stoi(attendance_line[2]) + 1 << endl;
            } else{
                attendance_write << attendance_line[1] << " " << stoi(attendance_line[2]) << endl;
            }
        }
    }

    attendance_read.close();
    attendance_write.close();

    remove("attendance.txt");
    rename("tmp.txt", "attendance.txt");

    sort_attendance_report("attendance.txt");
}

void print_out_attendance(){

    system("clear");

    int setw_value = 20;
    string line;
    string * user_attendance;

    cout << "\n\t\t    Attendance report" << endl;
    cout << "\t\t    ====================\n" << endl;
    cout << "\t\t" << setw(setw_value) << left << "Username" << setw(setw_value) << left << "Attendance" << endl;

    fstream attendace_read;
    attendace_read.open("attendance.txt", ios::in);
    while(getline(attendace_read, line)){
        user_attendance = split_by_space(line, get_space_count(line));
        cout << "\t\t" << setw(setw_value) << left << user_attendance[1] << setw(setw_value) << left << user_attendance[2] << endl;
    }
    attendace_read.close();
    wait();
}

void change_QNum(int NumChange){
    fstream QNum;
    QNum.open("QNum.txt", ios::out);
    QNum << NumChange;
    QNum.close();
}

change_password(string username, string new_password){

}
