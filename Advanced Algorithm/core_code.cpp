#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <limits>
#include <time.h>
#include <cstdlib>
#include "MyQueue.cpp"
//#include "file_op.cpp"

string logged_in_as = "a";
int privilege_status;

using namespace std;


void wait(){ // press ENTER key to continue the program
    cin.get();
    do{
        cout << "\nPress ENTER key to continue...";
    } while(cin.get() != '\n');
}

void under_maintainance_prompt(){
    system("clear");
    cout << "\n      Under Maintainance :(\n" << endl;
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

int get_int_input(){ // get integer only input
    int x;
    cout << "\nEnter a choice: "; cin >> x;

    // Using infinite loop for input validation
    while(1){
        if(cin.fail()) // Returns true when input fails
        {
            cin.clear(); // Use to clear error state of buffer

            // Ignores rest of the line
            // After first error occurs

            // Skips to the next line
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "\nPlease enter a valid input: ";
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
    cout << "1. Mathematics" << endl;
    cout << "2. Physics" << endl;
    cout << "3. English" << endl;
    cout << "4. Go back" << endl;
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
    string username, password;
    string * credential;
    cout << "Enter a new username: "; cin >> username;
    cout << "Enter a new password: "; cin >> password;
    if(privilege.compare("admin") == 0){
        credential = username_exists(username, "admin_credential.txt");
        if(credential[0].compare("0") == 0){
            add_user("admin_credential.txt", username, password);
            cout << "\nAdmin has been added..." << endl;
            privilege_status = 1;
            // change_read_privilege_file(1, "change");
        } else{
            cout << "\nUsername has already been taken..." << endl;
            privilege_status = -1;
            // change_read_privilege_file(-1, "change"); // Failure of admin log in
        }
    }else {
        credential = username_exists(username, "user_credential.txt");
        if(credential[0].compare("0")  == 0){
            add_user("user_credential.txt", username, password);
            privilege_status = 0;
            cout << "\nUser has been added..." << endl;
            // change_read_privilege_file(0, "change");
            logged_in_as = username;
        } else{
            cout << "\nUsername has already been taken..." << endl;
            privilege_status = -2;
            // change_read_privilege_file(-2, "change"); // Failure of user log in
        }
    }
}

void sign_in(string privilege){
    // Successful sign in: privilege.txt holds 1 for admin, 0 for user
    // Failed sign in: privilege.txt holds -1
    string username, password;
    string * credential;
    cout << "Enter your username: "; cin >> username;
    cout << "Enter your password: "; cin >> password;
    if(privilege.compare("admin") == 0){
        credential = username_exists(username, "admin_credential.txt");
        if(credential[0].compare("1")  == 0 && credential[2].compare(password) == 0){
            cout << "\nWelcome, admin " << credential[1] << "!" << endl;
            logged_in_as = credential[1];
            privilege_status = 1;
            // change_read_privilege_file(1, "change");
        } else {
            cout << "\nSign in is not successful!" << endl;
            privilege_status = -1;
            // change_read_privilege_file(-1, "change"); // Failure of admin log in
        }
    }else {
        credential = username_exists(username, "user_credential.txt");
        if(credential[0].compare("1")  == 0 && credential[2].compare(password) == 0){
            cout << "\nWelcome, " << credential[1] << "!" << endl;
            logged_in_as = credential[1];
            privilege_status = 0;
            // change_read_privilege_file(0, "change");
        } else {
            cout << "\nSign in is not successful!" << endl;
            privilege_status = -2;
            // change_read_privilege_file(-2, "change"); // Failure of user log in
        }
    }
}

void delete_credential(string file_path, string username){ // Removal of a user or an admin by an admin
    string * credential;
    credential = username_exists(username, "user_credential.txt");
    if(credential[0].compare("0") == 0){
        cout << "\nUser doesn't exist." << endl;
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
        cout << "\nUser has been deleted." << endl;
    }
}

void add_questions(string quiz_name){ // Add question to quiz_name
    fstream quiz;
    quiz.open(quiz_name, ios::app);
    int q_num;
    string input_text;
    cout << "\nYou are adding question(s) to " << quiz_name << endl;
    cout << "Enter the number of questions: "; cin >> q_num;
    cout << "\n";
    getline(cin, input_text);
    for(int i=0; i<q_num; i++){
        for(int j=0; j<6; j++){
            switch(j){
            case 0:
                cout << "Enter question number " << i + 1 << ": ";
                getline(cin, input_text);
                quiz << input_text << "\n";
                break;
            case 1:
                cout << "Enter answer A: ";
                getline(cin, input_text);
                quiz << input_text << "\n";
                break;
            case 2:
                cout << "Enter answer B: ";
                getline(cin, input_text);
                quiz << input_text << "\n";
                break;
            case 3:
                cout << "Enter answer C: ";
                getline(cin, input_text);
                quiz << input_text << "\n";
                break;
            case 4:
                cout << "Enter answer D: ";
                getline(cin, input_text);
                quiz << input_text << "\n";
                break;
            case 5:
                cout << "Enter the correct answer: ";
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
        cout << "\n" << quiz_name << " has no questions yet" << endl;
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
                    cout << "Question number " << cur_line/6 + 1 << ": ";
                    cout << line << endl;
                    break;
                case 2:
                    cout << "A. ";
                    cout << line << endl;
                    break;
                case 3:
                    cout << "B. ";
                    cout << line << endl;
                    break;
                case 4:
                    cout << "C. ";
                    cout << line << endl;
                    break;
                case 5:
                    cout << "D. ";
                    cout << line << endl;
                    break;
                case 6:
                    cout << "Correct answer: ";
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

    if(ID > get_num_of_q(quiz_name_ori)){
        cout << "\nID out of bound..." << endl;
        cout << "Maximum ID is " << get_num_of_q(quiz_name_ori) << endl;
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
    cout << "\nQuestion has been deleted." << endl;
}

void update_quizz(string quiz_name_ori, int ID){
    // Delete q by ID

    if(ID > get_num_of_q(quiz_name_ori)){
        cout << "\nID out of bound..." << endl;
        cout << "Maximum ID is " << get_num_of_q(quiz_name_ori) << endl;
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
                    cout << "Question number " << cur_line/6 + 1 << "\n";
                    cout << "\nCurrent question: " << line << endl;
                    cout << "New question: "; cin >> new_status;
                    cout << "\n";
                    temp << new_status;
                    temp << "\n";
                    break;
                case 2:
                    cout << "Current answer A: ";
                    cout << line << endl;
                    cout << "New answer: "; cin >> new_status;
                    cout << "\n";
                    temp << new_status;
                    temp << "\n";
                    break;
                case 3:
                    cout << "Current answer B: ";
                    cout << line << endl;
                    cout << "New answer: "; cin >> new_status;
                    cout << "\n";
                    temp << new_status;
                    temp << "\n";
                    break;
                case 4:
                    cout << "Current answer C: ";
                    cout << line << endl;
                    cout << "New answer: "; cin >> new_status;
                    cout << "\n";
                    temp << new_status;
                    temp << "\n";
                    break;
                case 5:
                    cout << "Current answer D: ";
                    cout << line << endl;
                    cout << "New answer: "; cin >> new_status;
                    cout << "\n";
                    temp << new_status;
                    temp << "\n";
                    break;
                case 0:
                    cout << "Current correct answer: ";
                    cout << line << endl;
                    cout << "New correct answer: "; cin >> new_status;
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
    cout << "\nQuestion has been updated." << endl;
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
        cout << "\nID out of bound..." << endl;
        cout << "Maximum ID is " << get_num_of_q(quiz_name_ori) << endl;
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


void take_a_quiz(string quiz_name){
    MyQueue *my_queue = createEmptyQueue();
    int q_num = get_num_of_q(quiz_name);
    ifstream file;
    file.open(quiz_name);
    cout << q_num << endl;
    if(file){
        if(q_num > 0){
            file.close();
        } else{
            cout << quiz_name << " has no questions yet!" << endl;
            return;
        }
    } else{
        cout << quiz_name << " has no questions yet!" << endl;
        return;
    }

    string line;

    double score;

    string user_ans, cor_ans;


    fstream quiz_file;

    int real_case_q_num;

    if(q_num >= 5){
            real_case_q_num = 5;
        } else{
            real_case_q_num = q_num;
        }

    int * random_ID;
    random_ID = randomize_ID(q_num, real_case_q_num);

    for(int i=0; i<real_case_q_num; i++){ // Loop through question
        add_q_to_queue(my_queue, quiz_name, random_ID[i]);
    }

    for(int k=0; k<real_case_q_num; k++){
        for(int i=1; i<=5; i++){
            switch(i){
            case 1:
                cout << "QCM, ID_"<< random_ID[k] << ": " << dequeue(my_queue) << endl;
                break;
            case 2:
                cout << "A. " << ": " << dequeue(my_queue) << endl;
                break;
            case 3:
                cout << "B. " << ": " << dequeue(my_queue) << endl;
                break;
            case 4:
                cout << "C. " << ": " << dequeue(my_queue) << endl;
                break;
            case 5:
                cout << "D. " << ": " << dequeue(my_queue) << endl;
                break;
            default:
                break;

            }
        }
        cout << "Enter your answer: "; cin >> user_ans;
        cor_ans = dequeue(my_queue);
        transform(user_ans.begin(), user_ans.end(), user_ans.begin(), ::toupper);
        transform(cor_ans.begin(), cor_ans.end(), cor_ans.begin(), ::toupper);
        cout << "\nCorrect answer: " << cor_ans << endl;
        cout << "Your answer: " << user_ans << endl << endl;;
        if(!user_ans.compare(cor_ans)){
            cout << "You got it :)" << endl;
            score++;
        } else{
            cout << "Sorry, you didn't get it :(" << endl;
            score -= 0.5;
        }
        wait();
        system("clear");
    }

    cout << "Score: " << score << endl;
    fstream score_record;
    score_record.open("score_record.txt", ios::app);
    score_record << logged_in_as << " " << quiz_name << " " << score << endl;
    score_record.close();

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

void sort_score_report(MyQueue *avg_record_queue, MyQueue *sorted_avg){

    string line, entry;
    double cur_max;
    fstream avg_record;
    avg_record.open("avg_record.txt", ios::in);
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

    sort_score_report(avg_record_queue, sorted_avg);

    int setw_value = 20;
    string * user_avg;

    cout << "\n    Average score report\n" << endl;
    cout << setw(setw_value) << left << "Username" << setw(setw_value) << left << "Average Score" << endl;

    fstream avg_record_write;
    avg_record_write.open("avg_record.txt", ios::out);
    Element *tmp;
    tmp = sorted_avg->front;
    while(tmp!=NULL){
        user_avg = split_by_space(tmp->data, get_space_count(tmp->data));
        cout << setw(setw_value) << left << user_avg[1] << setw(setw_value) << left << user_avg[2] << endl;
        avg_record_write << tmp->data << endl;
        tmp = tmp->next;
    }
    avg_record_write.close();
    wait();
}
