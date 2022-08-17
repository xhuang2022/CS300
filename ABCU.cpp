//============================================================================
// Name        : ABCU.cpp
// Author      : Xiao (Lindsey) Huang
// Date        : 08/12/2022
// Class       : CS 300
// Description : ABCU Project 2
//============================================================================

#include "Hashtable.h"
#include <iostream>
#include <algorithm>


void displayMenu() {
    cout << endl;
    cout << "What would like to do? " << endl;
    cout << "  1. Load Data Structure." << endl;
    cout << "  2. Print Course List." << endl;
    cout << "  3. Print Course." << endl;
    cout << "  9. Exit" << endl;
    cout << "Enter choice: " << endl;
}

int getMenuChoice() {
    int userInput = 0;
    while (!(cin >> userInput) || (userInput > 3 && userInput < 9)) {
        cout << userInput << " is not a valid option." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        displayMenu();    
    }
    return userInput;
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // Define a hash table to hold all the bids
    HashTable* courseTable;
    string fileName;
    string courseId;
    Courses course;
    courseTable = new HashTable();

    int choice = 0;
    cout << "Welcome to the course planner." << endl << endl;

    while (choice != 9) {
        displayMenu();
        
        choice = getMenuChoice();

        switch (choice) {

        case 1:
            //load the courses            
            cout << "Please enter a file name." << endl;
            cin >> fileName;
            courseTable->LoadCourse(fileName);        
            break;

        case 2:           
            cout << "Here is a sample schedule:  " << endl << endl;
            courseTable->PrintAll();
            break;

        case 3:
            cout << "What course do you want to know about? ";
            cin >> courseId;
            // convert courseId to uppercase
            transform(courseId.begin(), courseId.end(), courseId.begin(), ::toupper);
            
            course = courseTable->Search(courseId);

            if (!course.courseId.empty()) {
                courseTable->displayCourse(course);
            }
            else {
                cout << courseId << " not found." << endl;
            }
            break;
        }
    }
    cout << "Thank you for using the course planner!" << endl;

    return 0;
}
