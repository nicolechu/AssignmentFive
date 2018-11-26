/* Nicole Chu
 * 2290152
 * nichu@chapman.edu
 * 350-01
 * Assignment #5
 */

/*
 * The Student class contains functions that build a Student object, display student information,
   return a student's ID number, return a student's advisor's ID number, and set the student's advisor.
 */

#include <iostream>
#include "Student.h"

using namespace std;

// default constructor
Student::Student()
{
  studentID = 0;
  name = "";
  level = "";
  major = "";
  gpa = 0;
  advisorID = 0;
}

// prompts user for input in order to build Student object
void Student::build()
{
  // https://discuss.codechef.com/questions/38874/how-to-read-string-with-whitespace-in-c
  cout << "Enter the student's ID: ";
  cin >> studentID;
  cin.ignore();

  cout << "Enter the student's name: ";
  getline(cin, name);

  cout << "Enter the student's grade level: ";
  getline(cin, level);

  cout << "Enter the student's major: ";
  getline(cin, major);

  cout << "Enter the student's GPA: ";
  cin >> gpa;

  cout << "Enter the student's advisor's ID: ";
  cin >> advisorID;
}

// displays all information about a student
void Student::displayStudentInfo()
{
  cout << "Student ID: " << studentID << endl;
  cout << "Student Name: " << name << endl;
  cout << "Student Level: " << level << endl;
  cout << "Student Major: " << major << endl;
  cout << "Student GPA: " << gpa << endl;
  cout << "Student Advisor ID: " << advisorID << endl;
}

// returns student ID number (key for BST)
int Student::id()
{
  return studentID;
}

// returns student's advisor's ID (can be used to find advisor in Faculty BST)
int Student::advisor()
{
  return advisorID;
}

// used to reset a student's advisor (for instance, if previous advisor is deleted)
void Student::setAdvisor(int aID)
{
  advisorID = aID;
}
