#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


using namespace std;

// Do not change this function. It is used for checking the lab.
void prepare_files(){
    ofstream ofs ("student_list.txt");

    if (ofs){
        ofs << 20185639 << endl;
        ofs << 22435497 << endl;
        ofs << 23143658 << endl;
        ofs << 29372413 << endl;
        ofs << 29567638 << endl;
        ofs << 29576389 << endl;
    }

}


// Do not change this function. It is used for checking the lab.
void check_final_list(){
    ifstream ifs ("student_list.txt");
    if (ifs){
        int line;
        while (ifs >> line){
            cout << line << endl;
        }
        ifs.close();
    }
}


// TODO: search for a student in the input file, student_list.txt, return true if found.
bool student_lookup(int student_id){
    ifstream inputFile ("student_list.txt");
    
    int line; // 
    while(inputFile >> line){  // from input stream get every student id in student_list.txt
        if ( line == student_id ){
            inputFile.close();
            return true; // immediate return true if found;
        }
    }
    inputFile.close();
    return false; //none of the id is found.

}


// TODO: delete a student id from the input file.
// The result should not contain blank lines
// Please check the section "Hint" in the lab page for how to rename a file or remove a file.
void delete_student(int student_id){
    ofstream outputFile ("student_list.txt",ios::app);
    ofstream tempFile ("temp.txt");
    ifstream inputFile("student_list.txt");

    vector<int> data;
    int line;
  

    if(student_lookup(student_id)){ //check if id exist
        while(inputFile>>line){
            data.push_back(line);
        }
      
        for(vector<int>::iterator i = data.begin(); i != data.end(); i++)
        {
            if( *i == student_id)
                data.erase(i);
        }

        for(vector<int>::iterator i = data.begin(); i != data.end(); i++)
        {
            tempFile << *i << endl;
        }
        
        outputFile.close(); // close f
        inputFile.close();
        tempFile.close();

        if (remove("student_list.txt") == 0)
            cout << "The file is successfully removed" << endl;
        else
            cout << "Error removing file" << endl;

        if (rename("temp.txt","student_list.txt") == 0)
            cout << "The file is successfully renamed" << endl;
        else
            cout << "Error renaming file" << endl;
        
        cout <<"Student " << student_id << " is removed from the course!" << endl;

    }

    else{
         cerr <<"Student " << student_id << " is not taking the course!" << endl;
    }

}


// TODO: insert a student in the input file such that the student ids are in ascending order
// It should not insert duplicate student id.
// Please check the section "Hint" in the lab page for how to rename a file or remove a file.
void insert_student(int student_id){
    ofstream outputFile ("student_list.txt",ios::app);
    ofstream tempFile ("temp.txt");
    ifstream inputFile("student_list.txt");

    vector<int> data;
    int line;
  

    if(!student_lookup(student_id)){ //check if id duplicate
        outputFile << student_id << endl;
        while(inputFile>>line){
            data.push_back(line);
        }
        sort(data.begin(),data.end());

        for(vector<int>::iterator i = data.begin(); i != data.end(); i++)
        {
            tempFile << *i << endl;
        }
        
        outputFile.close(); // close first
        inputFile.close();
        tempFile.close();

        if (remove("student_list.txt") == 0)
            cout << "The file is successfully removed" << endl;
        else
            cout << "Error removing file" << endl;

        if (rename("temp.txt","student_list.txt") == 0)
            cout << "The file is successfully renamed" << endl;
        else
            cout << "Error renaming file" << endl;
        
        cout <<"Student " << student_id << " is inserted successfully!" << endl;

    }

    else{
         cerr <<"Student " << student_id << " is already taking the course!" << endl;
    }

}

int main(){

    const char filename[] = "student_list.txt";
    char choice;
    int student_id;

    prepare_files();

    while (true){       

        cout << "1 for lookup; 2 for insertion; 3 for deletion; q for quit: ";
        cin >> choice;

        if (choice == '1'){
            cout << "Please enter the id of the student you want to search for: ";
            cin >> student_id;
            if (student_lookup(student_id)){
                cout << "Student " << student_id << " is found!" << endl;
            }else{
                cout << "Student " << student_id << " is not found!" << endl;
            }
        }else if (choice == '2'){
            cout << "Please enter the id of the student you want to insert: ";
            cin >> student_id;
            insert_student( student_id);
        }else if (choice == '3'){
            cout << "Please enter the id of the student you want to delete: ";
            cin >> student_id;
            delete_student(student_id);
        }else if (choice == 'q'){
            check_final_list();
            break;
        }else{
            cout << "Invalid input. Please input again." << endl;
        }
        cout << endl;
    }

    return 0;
}