/* Nicole Chu
 * 2290152
 * nichu@chapman.edu
 * 350-01
 * Assignment #5
 */

/*
 * This is my Doubly-Linked List template class. It contains functions to insert and remove elements to my list,
   print my list, find or remove specific elements in my list, and return the size of my list.
 */

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>
#include "ListNode.h"

using namespace std;

template <class T>
class DoublyLinkedList
{
public:
  DoublyLinkedList();

  void destruct();
  void insertFront(T d);
  void insertBack(T d);
  T removeFront();
  T removeBack();
  T getFront();
  T getBack();
  void printList() const;
  int find(T val);
  unsigned int getSize();
  T deletePos(int pos);
  T remove(T key);
  ListNode<T>* frontNode() const;
  bool isEmpty();

private:
  ListNode<T> *front;
  ListNode<T> *back;
  unsigned int size; // unsigned = not negative
};

/*
 * The default constructor sets the front and back pointers to null & the size variable to zero upon declaration
   of a list object.
 */
template <class T>
DoublyLinkedList<T>::DoublyLinkedList()
{
  front = NULL;
  back = NULL;
  size = 0;
}

/*
 * destruct function
 * This function manually destructs my list. I found this code on:
   https://www.includehelp.com/code-snippets/implementation-of-queue-using-linked-list-in-cpp.aspx
 */
template <class T>
void DoublyLinkedList<T>::destruct()
{
  while(front!=NULL)
  {
      ListNode<T> *temp = front;
      front = front->next;
      delete temp;
  }
  back = NULL;

  cout << "Destroyed" << endl;
}

/*
 * getSize function
 * This returns the size of the list.
 */
template <class T>
unsigned int DoublyLinkedList<T>::getSize()
{
  return size;
}

/*
 * printList function
 * This outputs the entire list to the user.
 */
template <class T>
void DoublyLinkedList<T>::printList() const
{
  ListNode<T> *curr = front;

  while(curr) // while curr is not NULL
  {
    cout << curr->data << endl;
    curr = curr->next;
  }
}

template <class T>
bool DoublyLinkedList<T>::isEmpty()
{
  return front == NULL;
}

/*
 * insertFront function
 * The insertFront function inserts an element at the front of the list.
 */
template <class T>
void DoublyLinkedList<T>::insertFront(T d)
{
  ListNode<T> *node = new ListNode<T>(d);

  if(size == 0) // if list is empty
  {
    back = node;
  }
  else
  {
    front->prev = node;
    node->next = front;
  }

  front = node;
  size++;
}

/*
 * insertBack function
 * The insertBack function inserts an element at the back of the list (which is called from my Queue class).
 */
template <class T>
void DoublyLinkedList<T>::insertBack(T d)
{
  ListNode<T> *node = new ListNode<T>(d);

  if(size == 0) // if list is empty
  {
    front = node;
  }
  else
  {
    back->next = node;
    node->prev = back;
  }

  back = node;
  size++;
}

/*
 * removeFront function
 * The removeFront function deletes the element at the front of the list and is called from the Queue class.
 * I had to slightly alter this code from what we programmed in class because it was giving me errors when
   I tried to remove elements from a queue in multiple functions.
 */
template <class T>
T DoublyLinkedList<T>::removeFront()
{
  ListNode<T> *temp = front;

  if(front->next == NULL) // if there's only one node
  {
    back = NULL; // the list will be empty
  }
  else
  {
    front->next->prev = NULL;
  }

  T val = temp->data;
  front = front->next;

  size--;

  return val;
}

/*
 * removeBack function
 * The removeBack function removes the element at the end of the list.
 */
template <class T>
T DoublyLinkedList<T>::removeBack()
{
  ListNode<T> *temp = back;

  if(back->prev == NULL) // if there's only one node
  {
    front = NULL; // the list will be empty
  }
  else
  {
    back->prev->next = NULL;
  }

  back = back->prev;
  temp->prev = NULL;
  T val = temp->data;

  delete temp;
  size--;

  return val;
}

/*
 * getFront function
 * The getFront function returns the element at the front of the list and is called in the Queue peek function.
 */
template <class T>
T DoublyLinkedList<T>::getFront()
{
  return front->data;
}

template <class T>
ListNode<T>* DoublyLinkedList<T>::frontNode() const
{
  return front;
}

/*
 * getBack function
 * The getBack function returns the element at the end of the list.
 */
template <class T>
T DoublyLinkedList<T>::getBack()
{
  return back->data;
}

/*
 * remove function
 * This function removes and returns a specific element from the list.
 */
template <class T>
T DoublyLinkedList<T>::remove(T key)
{
  ListNode<T> *current = front;

  while(current->data != key)
  {
    current = current->next;

    /*
    if(current == NULL)
    {
      return NULL;
    }
    */
  }

  if(current == front)
  {
    front = current->next;
  }
  else
  {
    current->prev->next = current->next;
  }

  if(current == back)
  {
    back = current->prev;
  }
  else
  {
    current->next->prev = current->prev;
  }

  current->next = NULL;
  current->prev = NULL;

  --size;

  return current->data;
}

/*
 * find function
 * This function finds & returns the index of a specific element from the list.
 */
template <class T>
int DoublyLinkedList<T>::find(T val)
{
  int idx = 1;
  ListNode<T> *curr = front;

  while(curr != NULL)
  {
    ++idx;
    if(curr->data == val)
    {
      break;
    }
    else
    {
      curr = curr->next;
    }
  }

  if(curr == NULL)
  {
    idx = -1;
  }

  return idx;
}

/*
 * deletePos function
 * The deletePos function removes & returns an element of the list at a specific index.
 */
template <class T>
T DoublyLinkedList<T>::deletePos(int pos)
{
  int idx = 0;
  ListNode<T> *prev = front;
  ListNode<T> *curr = front;

  while(idx != pos)
  {
    prev = curr;
    curr = curr->next;
    ++idx;
  }

  prev->next = curr->next;
  curr->next = NULL;
  T d = curr->data;
  size--;
  delete curr;
  return d;
}

#endif
