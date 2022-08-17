//============================================================================
// Name        : Hashtable.cpp
// Author      : Xiao (Lindsey) Huang
// Date        : 08/12/2022
// Class       : CS 300
// Description : ABCU Project 2
//============================================================================

#include "Hashtable.h"
#include <algorithm>
#include <climits>
#include <iostream>
#include <fstream>

/**
 * Default constructor
 */
HashTable::HashTable() {
    // Initalize node structure by resizing tableSize
    nodes.resize(tableSize);
}

/**
 * Constructor for specifying size of the table
 */
HashTable::HashTable(unsigned int size) {
    // invoke local tableSize to size with this->
    this->tableSize = size;
    // resize nodes size
    nodes.resize(tableSize);
}
/**
 * Destructor
 */
HashTable::~HashTable() {
    // for node begin to end iterate
    for (auto i = nodes.begin(); i != nodes.end(); i++) {
        Node* next = i->next;
        while (next != NULL) {
            Node* temp = next;
            next = temp->next;
            delete temp;
        }
    }
}
//Calculate the hash value of a given key.
unsigned int HashTable::hash(string& key) {
    // return key tableSize
    return  std::hash<string>{}(key) % tableSize;
}

//Insert a course
void HashTable::Insert(Courses course) {
    // create the key for the given course
    unsigned int key = hash(course.courseId); //convert a string of a word into integer for hash index 
    // retrieve node using key
    Node* currentNode = &nodes[key]; // hash position

    // if no entry found for the key
    // assign this node to the key position and bid information
    if (currentNode->key == UINT_MAX) {
        currentNode->course = course;
        currentNode->key = key;
        currentNode->next = nullptr;
    }

    /** if there's an entry in the head of key bucket
    * loop until there's an empty node to store the course information and key
    */
    else {
        while (currentNode->next != nullptr) {
            currentNode = currentNode->next;
        }
        currentNode->next = new Node(course, key);
    }
}

// Display the course information 
void HashTable::displayCourse(Courses course) {
    cout << course.courseId << ", " << course.courseName << endl;
    if (course.prerequisites.size() != 0) {
        cout << "Prerequisites: ";
        for (unsigned int i = 0; i < course.prerequisites.size(); i++) {
            cout << course.prerequisites[i] << " ";
        }
        cout << endl;
    }
}

/**
 * Print all courses in alphanumeric order
 */
void HashTable::PrintAll() {
    Courses course;
    // from beginning of CourseList to the end 
    for (unsigned int i = 0; i < CourseList.size(); i++) {
        course = Search(CourseList[i]);
        cout << course.courseId << ", " << course.courseName << endl;
    }
}

//Search for the specified coursedId
Courses HashTable::Search(string courseId) {
    Courses course;
    // create the key for the given courseId
    unsigned int key = hash(courseId);  //convert a string into integer 
    Node* currentNode = (&nodes[key]);  // hash position

    // if the match is at the begin(head) of hash table
    if (currentNode->course.courseId == courseId) {
        return currentNode->course;
    }
    // if not match, loop through the key bucket to look for a match 
    currentNode = currentNode->next;
    while (currentNode != nullptr && currentNode->course.courseId != courseId) {
        currentNode = currentNode->next;
    }
    // if no match found
    if (currentNode != nullptr) {
        return currentNode->course;
    }
    return course;
}

//Load a CSV file containing courses into a container
void HashTable::LoadCourse(string fileName) {
    vector <string> updatedPrerequsites;
    Courses course;
    vector <string> tokens;
    string line, token;
    ifstream ifile;

    ifile.open(fileName);
    if (!ifile.is_open()) {
        cout << "Unable to open file." << endl;
    }
    else {
        while (ifile.good()) {
            while (getline(ifile, line)) {
                stringstream linestream(line);
                while (getline(linestream, token, ',')) {
                    tokens.push_back(token);
                }
                if (tokens.size() < 2) {
                    continue;
                }
                course.courseId = tokens[0];
                course.courseName = tokens[1];
                CourseList.push_back(course.courseId); //add courseID in the vector to be sorted
                if (tokens.size() > 2) {
                    for (unsigned int i = 2; i < tokens.size(); i++) {
                        course.prerequisites.push_back(tokens[i]);
                    }
                }
                Insert(course);
                tokens.clear(); // clear the tokens vector 
                course.prerequisites.clear(); //clear prerequisites vector to remove previous stored courseID
            }
        }
    }
    ifile.close();

    sort(CourseList.begin(), CourseList.end()); //sort the courseID to use in print method
    //Validate the prerequisites 
    for (auto it = nodes.begin(); it != nodes.end(); it++) {
        Node* currentNode = &(*it);
        if (currentNode->key == UINT_MAX) {
            continue;
        }
        while (currentNode != nullptr) {
            for (unsigned int i = 0; i < currentNode->course.prerequisites.size(); i++) {
                course = Search(currentNode->course.prerequisites[i]);
                if (!course.courseId.empty()) {
                    updatedPrerequsites.push_back(course.courseId);
                }
            }
            currentNode->course.prerequisites = updatedPrerequsites;
            updatedPrerequsites.clear();
            currentNode = currentNode->next;
        }
    }
}
