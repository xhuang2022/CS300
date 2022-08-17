//============================================================================
// Name        : Hashtable.hpp
// Author      : Xiao (Lindsey) Huang
// Date        : 08/12/2022
// Class       : CS 300
// Description : ABCU Project 2
//============================================================================


#pragma once
#ifndef _HASHTABLE_HPP_
#define _HASHTABLE_HPP_
#include <iostream>
#include <string>
#include <sstream> 
#include <vector>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

const unsigned int DEFAULT_SIZE = 12;

// define a structure to hold course information
struct Courses {
    string courseId;
    string courseName;
    vector<string> prerequisites;
};
//============================================================================
// Hash Table class definition
//============================================================================

/**
 * implement a hash table with chaining.
 */
class HashTable {

private:
    // Define structures to hold courses
    struct Node {
        Courses course;
        unsigned int key;
        Node* next;

        // default constructor
        Node() {
            key = UINT_MAX;
            next = nullptr;
        }

        // initialize with a course
        Node(Courses aCourse) : Node() {
            course = aCourse;
        }

        // initialize with a course and a key
        Node(Courses aCourse, unsigned int aKey) : Node(aCourse) {
            key = aKey;
        }
    };

    vector<Node> nodes;
    unsigned int tableSize = DEFAULT_SIZE;
    unsigned int hash(string& key);

public:
    HashTable();
    HashTable(unsigned int size);
    virtual ~HashTable();
    void Insert(Courses course);
    void PrintAll();
    void LoadCourse(string filename);
    Courses Search(string courseId);
    vector <string> CourseList;
    void displayCourse(Courses course);
};
#endif // !_HASHTABLE_HPP_
