/* Nicole Chu
 * 2290152
 * nichu@chapman.edu
 * 350-01
 * Assignment #5
 */

/*
 * This is the header file for the Student class. It contains class function and variable declarations
   as well as code to override certain operators including ==, <, >, and <<.
 */

#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

using namespace std;

class Student
{
public:
  Student();

  int id(); // return id number (key for BST nodes) ? needed??
  void displayStudentInfo(); // param's for specific student??
  int advisor();
  void setAdvisor(int aID);
  void build();

  bool operator==(const Student& s)
  {
    return this->studentID == s.studentID;
  }

  bool operator<(const Student& s)
  {
    return this->studentID < s.studentID;
  }

  bool operator>(const Student& s)
  {
    return this->studentID > s.studentID;
  }

  // https://msdn.microsoft.com/en-us/library/1z2f6c2k.aspx
  friend ostream& operator<<(ostream& os, const Student& s)
  {
    os << "Student ID: " << s.studentID <<
    "\nStudent Name: " << s.name <<
    "\nStudent Level: " << s.level <<
    "\nStudent Major: " << s.major <<
    "\nStudent GPA: " << s.gpa <<
    "\nStudent Advisor ID: " << s.advisorID;
    return os;
  }

private:
  int studentID;
  string name;
  string level;
  string major;
  double gpa;
  int advisorID;
};

#endif
