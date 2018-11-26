/* Nicole Chu
 * 2290152
 * nichu@chapman.edu
 * 350-01
 * Assignment #5
 */

/*
 * This is the TreeNode template class which contains constructors, an object of type T, an int key,
   and two left and right node pointers.
 */

#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>

using namespace std;

template <typename T>
class TreeNode
{
public:
  TreeNode();
  TreeNode(T o, int k);
  virtual ~TreeNode(); // virtual = ...

  T object;
  int key; // int id key or object key?
  TreeNode<T> *left;
  TreeNode<T> *right;
};

template <typename T>
TreeNode<T>::TreeNode()
{
  left = NULL;
  right = NULL;
}

template <typename T>
TreeNode<T>::TreeNode(T o, int k)
{
  left = NULL;
  right = NULL;
  object = o;
  key = k;
}

template <typename T>
TreeNode<T>::~TreeNode()
{
  //destructor
}

#endif
