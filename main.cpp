/* Nicole Chu
 * 2290152
 * nichu@chapman.edu
 * 350-01
 * Assignment #5
 */

/*
 * This is the main file which will check if two files exist which contain BST's to be read into the
   program. It also contains code to display the menu to the user and obtains the appropriate input
   based on the user's menu selection.
 */

#include <iostream>
#include <fstream>
#include "Faculty.cpp"
#include "Student.cpp"
#include "BST.h"

using namespace std;

int main()
{
  BST<Faculty> masterFaculty;
  BST<Student> masterStudent;
  ifstream facultyInput;
  ifstream studentInput;
  ofstream facultyFile;
  ofstream studentFile;

  /*
   * This block of code checks if the facultyTable and studentTable files exist in the directory.
     If they do, their information is stored in the faculty and student BST's. If not, masterFaculty
     and masterStudent are initialized as empty.
   */
  if(ifstream("facultyTable.txt") && ifstream("studentTable.txt"))
  {
    cout << "found" << endl;
    facultyInput.open("facultyTable.txt");
    studentInput.open("studentTable.txt");
    // deserialize bst's
  }
  else
  {
    facultyFile.open("facultyTable.txt");
    studentFile.open("studentTable.txt");
  }

  // variables used for rollback
  DoublyLinkedList<Faculty> facultyTree;
  DoublyLinkedList<Student> studentTree;
  DoublyLinkedList<int> trackSel;

  int selection = 0;

  // while menu choice is not 14 (exit)
  while(selection != 14)
  {
    int student;
    int faculty;

    // display menu to user
    cout << "MENU:" << endl;
    cout << "1. Print all students & their info" << endl;
    cout << "2. Print all faculty & their info" << endl;
    cout << "3. Find & display student info" << endl;
    cout << "4. Find & display faculty info" << endl;
    cout << "5. Print name & info of a student's advisor" << endl;
    cout << "6. Print all names & info of a faculty member's advisees" << endl;
    cout << "7. Add new student" << endl;
    cout << "8. Delete a student" << endl;
    cout << "9. Add new faculty member" << endl;
    cout << "10. Delete a faculty member" << endl;
    cout << "11. Change a student's advisor" << endl;
    cout << "12. Remove an advisee from a faculty member" << endl;
    cout << "13. Rollback" << endl;
    cout << "14. Exit" << endl;

    // get user's menu selection
    cout << "\nEnter a number from the menu above: ";
    cin >> selection;

    // switch case for different menu selections
    switch(selection)
    {
      case 1: // print all student info
        masterStudent.printTree();
        break;
      case 2: // print all faculty info
        masterFaculty.printTree();
        break;
      case 3: // find a student
      {
        cout << "Enter the student's ID: ";
        cin >> student;
        if(masterStudent.contains(student))
        {
          Student s = masterStudent.find(student);
          s.displayStudentInfo();
        }
        else
        {
          cout << "ERROR: Student does not exist" << endl;
        }
        break;
      }
      case 4: // find a faculty
      {
        cout << "Enter the faculty member's ID: ";
        cin >> faculty;
        if(masterFaculty.contains(faculty))
        {
          Faculty f = masterFaculty.find(faculty);
          f.displayFacultyInfo();
        }
        else
        {
          cout << "ERROR: Faculty member does not exist" << endl;
        }
        break;
      }
      case 5: // find a student's advisor
      {
        cout << "Enter the student's ID: ";
        cin >> student;
        if(masterFaculty.contains(student))
        {
          Student s = masterStudent.find(student);
          if(masterFaculty.contains(s.advisor()))
          {
            Faculty f = masterFaculty.find(s.advisor());
            f.displayFacultyInfo();
          }
          else
          {
            cout << "ERROR: Student's advisor does not exist" << endl;
          }
        }
        else
        {
          cout << "ERROR: Student does not exist" << endl;
        }
        break;
      }
      case 6: // find a faculty's advisees
      {
        cout << "Enter the faculty member's ID: ";
        cin >> faculty;
        if(masterFaculty.contains(faculty))
        {
          Faculty f = masterFaculty.find(faculty);

          // iterate through list, print out each student
          ListNode<int> *curr = f.advisees.frontNode();

          while(curr) // while curr is not NULL
          {
            if(masterStudent.contains(curr->data))
            {
              Student s = masterStudent.find(curr->data);
              s.displayStudentInfo();
            }
            else
            {
              cout << "ERROR: Faculty's advisee does not exist" << endl;
            }
            curr = curr->next;
          }
        }
        else
        {
          cout << "ERROR: Faculty member does not exist" << endl;
        }

        break;
      }
      case 7: // add a new student
      {
        Student temp;
        temp.build();
        Student s = temp;
        masterStudent.insert(temp, temp.id());

        // add node to list, -1 added to trackSel list
        studentTree.insertBack(temp);
        if(studentTree.getSize() > 5)
        {
          studentTree.removeFront();
          //trackSel.removeFront();
        }
        trackSel.insertBack(-1);

        break;
      }
      case 8: // delete a student
      {
        cout << "Enter the student's ID: ";
        cin >> student;

        if(masterStudent.contains(student))
        {
          Student s = masterStudent.find(student);

          // add old node to list, 1 added to trackSel list
          studentTree.insertBack(s);
          if(studentTree.getSize() > 5)
          {
            studentTree.removeFront();
            //trackSel.removeFront();
          }
          trackSel.insertBack(1);

          // remove student from advisor's list
          Faculty f = masterFaculty.find(s.advisor());
          f.removeAdvisee(student);

          // delete student
          masterStudent.deleteRec(student);
        }
        else
        {
          cout << "ERROR: Student does not exist" << endl;
        }
        break;
      }
      case 9: // add a new faculty
      {
        Faculty temp;
        temp.build();
        masterFaculty.insert(temp, temp.id());

        // add node to list, -2 added to trackSel list
        facultyTree.insertBack(temp);
        if(facultyTree.getSize() > 5)
        {
          facultyTree.removeFront();
          //trackSel.removeFront();
        }
        trackSel.insertBack(-2);

        break;
      }
      case 10: // delete a faculty
      {
        cout << "Enter the faculty member's ID: ";
        cin >> faculty;

        if(masterFaculty.contains(faculty))
        {
          Faculty f = masterFaculty.find(faculty);

          // add old node to list, 2 added to trackSel list
          facultyTree.insertBack(f);
          if(facultyTree.getSize() > 5)
          {
            facultyTree.removeFront();
            //trackSel.removeFront();
          }
          trackSel.insertBack(2);

          // advisees need new advisors
          int temp;
          while(!f.noAdvisees())
          {
            int adv = f.popAdvisee();
            cout << "Enter new advisor ID for student " << adv << ": ";
            cin >> temp;
            if(masterFaculty.contains(temp))
            {
              Faculty f1 = masterFaculty.find(temp);
              f1.addAdvisee(adv);
            }
          }
        }
        masterFaculty.deleteRec(faculty);
        break;
      }
      case 11: // change student's advisor
      {
        cout << "Enter the student's ID: ";
        cin >> student;
        if(masterStudent.contains(student))
        {
          Student s = masterStudent.find(student);

          if(masterFaculty.contains(s.advisor()))
          {
            Faculty oldA = masterFaculty.find(s.advisor());
            cout << "Enter the new advisor's (faculty) ID: ";
            cin >> faculty;

            if(masterFaculty.contains(faculty))
            {
              Faculty newA = masterFaculty.find(faculty);
              // change old advisor's list
              oldA.removeAdvisee(student);
              // change student's advisor
              s.setAdvisor(faculty);
              // change new advisor's list
              newA.addAdvisee(student);
            }
            else
            {
              cout << "ERROR: Student's new advisor does not exist" << endl;
            }
          }
          else
          {
            cout << "ERROR: Student's current advisor does not exist" << endl;
          }
        }
        else
        {
          cout << "ERROR: Student does not exist" << endl;
        }
        break;
      }
      case 12: // remove an advisee from a faculty
      {
        cout << "Enter the faculty member's ID: ";
        cin >> faculty;
        if(masterFaculty.contains(faculty))
        {
          Faculty f = masterFaculty.find(faculty);

          cout << "Enter the advisees's ID: ";
          cin >> student;
          if(masterStudent.contains(student))
          {
            Student s = masterStudent.find(student);
            f.removeAdvisee(student);
            // give student new advisor
            int newA;
            cout << "Enter the student's new advisor's ID: ";
            cin >> newA;

            if(masterFaculty.contains(newA))
            {
              s.setAdvisor(newA);
            }
            else
            {
              cout << "ERROR: Faculty member does not exist" << endl;
            }
          }
          else
          {
            cout << "ERROR: Student does not exist" << endl;
          }
        }
        else
        {
          cout << "ERROR: Faculty member does not exist" << endl;
        }
        break;
      }
      case 13: // rollback
      {
        // student
        if(trackSel.getBack() == -1)
        {
          Student temp = studentTree.removeBack();
          masterStudent.deleteRec(temp.id());
          trackSel.removeBack();
        }
        else if(trackSel.getBack() == 1)
        {
          Student temp = studentTree.removeBack();
          masterStudent.insert(temp, temp.id());
          trackSel.removeBack();
        }
        // faculty
        else if(trackSel.getBack() == -2)
        {
          Faculty temp = facultyTree.removeBack();
          masterFaculty.deleteRec(temp.id());
          trackSel.removeBack();
        }
        else if(trackSel.getBack() == 2)
        {
          Faculty temp = facultyTree.removeBack();
          masterFaculty.insert(temp, temp.id());
          trackSel.removeBack();
        }
        break;
      }
      case 14: // exit
        // print trees to files using serialization function
        masterFaculty.serialize(facultyFile);
        masterStudent.serialize(studentFile);
        break;
    }
  }

  return 0;
}
