/* Nicole Chu
 * 2290152
 * nichu@chapman.edu
 * 350-01
 * Assignment #5
 */

/*
 * The Faculty class contains functions to display faculty information to the user, build a Faculty object,
   add and remove advisees from the advisee list, return the faculty's ID number, pop advisees from the
   advisee list, and return true if the advisee list is empty.
 */

#include <iostream>
#include "Faculty.h"

using namespace std;

// default constructor
Faculty::Faculty()
{
  facultyID = 0;
  name = "";
  level = "";
  department = "";
}

// displays all information about a faculty member
void Faculty::displayFacultyInfo()
{
  cout << "Faculty ID: " << facultyID << endl;
  cout << "Faculty Name: " << name << endl;
  cout << "Faculty Level: " << level << endl;
  cout << "Faculty Department: " << department << endl;
  cout << "Advisees: " << endl;
  advisees.printList();
}

// prompts user for input in order to build Faculy object
void Faculty::build()
{
  cout << "Enter the faculty's ID: ";
  cin >> facultyID;
  cin.ignore();

  cout << "Enter the faculty's name: ";
  getline(cin, name);

  cout << "Enter the faculty's level: ";
  getline(cin, level);

  cout << "Enter the faculty's department: ";
  getline(cin, department);

  // add advisees to list using while loop
  string adv;
  cout << "Add advisees? (y/n): ";
  cin >> adv;

  if(adv == "Y" || adv == "y")
  {
    string s = "y";
    while(s == "Y" || s == "y")
    {
      addAdvisees();

      cout << "Does the faculty have more advisees? (y/n): ";
      cin >> s;
    }
  }
}

// returns faculty ID number (key for the BST)
int Faculty::id()
{
  return facultyID;
}

// prompts user for advisee ID numbers to add to advisee list
void Faculty::addAdvisees()
{
  int sID;
  cout << "Enter the faculty's advisee's ID: ";
  cin >> sID;
  advisees.insertFront(sID);
}

// used to remove a specific advisee (for instance, when deleting a student)
int Faculty::removeAdvisee(int adv)
{
  return advisees.remove(adv);
}

// used to add a specific advisee to list
void Faculty::addAdvisee(int adv)
{
  advisees.insertFront(adv);
}

// used to iterate through advisee list (when a faculty member is deleted & advisees need new advisor)
int Faculty::popAdvisee()
{
  advisees.removeFront();
}

// returns true if the advisee list is empty
bool Faculty::noAdvisees()
{
  return advisees.isEmpty();
}
