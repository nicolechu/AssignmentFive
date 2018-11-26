/* Nicole Chu
 * 2290152
 * nichu@chapman.edu
 * 350-01
 * Assignment #5
 */

/*
 * This is the header file for the Faculty class. It contains class function and variable declarations
   as well as code to override certain operators including ==, <, >, and <<.
 */

#ifndef FACULTY_H
#define FACULTY_H

#include <iostream>
#include "DoublyLinkedList.h"

using namespace std;

class Faculty
{
public:
  Faculty();

  int id();
  void displayFacultyInfo();
  void addAdvisees();
  void addAdvisee(int adv);
  int removeAdvisee(int adv);
  int popAdvisee();
  bool noAdvisees();
  void build();

  bool operator==(const Faculty& f)
  {
    return this->facultyID == f.facultyID;
  }

  bool operator<(const Faculty& f)
  {
    return this->facultyID < f.facultyID;
  }

  bool operator>(const Faculty& f)
  {
    return this->facultyID > f.facultyID;
  }

  // https://msdn.microsoft.com/en-us/library/1z2f6c2k.aspx
  friend ostream& operator<<(ostream& os, const Faculty& f)
  {
    os << "Faculty ID: " << f.facultyID <<
    "\nFaculty Name: " << f.name <<
    "\nFaculty Level: " << f.level <<
    "\nFaculty Department: " << f.department <<
    "\nAdvisees: ";

    ListNode<int> *curr = f.advisees.frontNode();

    while(curr) // while curr is not NULL
    {
      os << "\n" << curr->data;
      curr = curr->next;
    }
    return os;
  }

  DoublyLinkedList<int> advisees;

private:
  int facultyID;
  string name;
  string level;
  string department;
};

#endif
