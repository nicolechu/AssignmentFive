/* Nicole Chu
 * 2290152
 * nichu@chapman.edu
 * 350-01
 * Assignment #5
 */

/*
 * This is the ListNode class which creates a ListNode object with prev & next pointers to be used in the DoublyLinkedList class.
 */

#ifndef LISTNODE_H
#define LISTNODE_H

#include <iostream>

using namespace std;

template <class T>
class ListNode
{
public:
  ListNode();
  ListNode(T d);
  ListNode *next;
  ListNode *prev;
  T data;
};

template <class T>
ListNode<T>::ListNode()
{
  //default constructor
}

template <class T>
ListNode<T>::ListNode(T d)
{
  data = d;
  next = NULL;
  prev = NULL;
}


#endif
