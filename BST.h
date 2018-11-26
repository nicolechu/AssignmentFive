/* Nicole Chu
 * 2290152
 * nichu@chapman.edu
 * 350-01
 * Assignment #5
 */

/*
 * This is my BST template class. It contains functionality for a binary search tree including insertion, find, deletion,
   print, contains, and serialization.
 */

#ifndef BST_H
#define BST_H

#include <iostream>
#include <fstream>
#include "TreeNode.h"

using namespace std;

template <typename T>
class BST
{
public:
  BST();
  virtual ~BST();

  void destroy(TreeNode<T> *node);

  void insert(T obj, int value);
  T find(int value);
  void deleteRec(int k);

  bool isEmpty();
  bool contains(int value);
  TreeNode<T>* getSuccessor(TreeNode<T> *d);

  void printTree();
  void recPrint(TreeNode<T> *node);

  void serialize(ofstream& filename);
  void recSerialize(TreeNode<T> *node, ofstream& filename);
  // void recDeserialize(TreeNode<T> *node, ifstream& filename);

private:
  TreeNode<T> *root;
};

template <class T>
BST<T>::BST()
{
  root = NULL;
}

//https://stackoverflow.com/questions/34170164/destructor-for-binary-search-tree
template <class T>
BST<T>::~BST()
{
  destroy(root);
}

template <class T>
void BST<T>::destroy(TreeNode<T> *node)
{
  if(node != NULL)
  {
    destroy(node->left);
    destroy(node->right);
    delete node;
  }
}

template <typename T>
void BST<T>::printTree()
{
  recPrint(root);
}

template <typename T>
void BST<T>::recPrint(TreeNode<T> *node)
{
  if(node == NULL)
    return;
  recPrint(node->left);
  cout << node->object << "\n\n";
  recPrint(node->right);
}

template <typename T>
bool BST<T>::isEmpty()
{
  return root == NULL;
}

template <typename T>
void BST<T>::insert(T obj, int value)
{
  TreeNode<T> *node = new TreeNode<T>(obj, value);

  if(isEmpty())
  {
    root = node;
  }
  else
  {
    TreeNode<T> *current = root;
    TreeNode<T> *parent; //empty node

    while(true)
    {
      parent = current;

      if(value < current->key) //go left
      {
        current = current->left;

        if(current == NULL) //insertion point found
        {
          parent->left = node;
          break;
        }
      }
      else //go right
      {
        current = current->right;

        if(current == NULL) //insertion point found
        {
          parent->right = node;
          break;
        }
      }
    }
  }
}

template <typename T>
bool BST<T>::contains(int value)
{
  if(isEmpty())
  {
    return false;
  }
  else //look for value
  {
    TreeNode<T> *current = root;

    while(current->key != value) //search for value
    {
      if(current == NULL)
        return false;

      if(value < current->key) //go left
        current = current->left;
      else
        current = current->right;
    }
  }
  return true;
}

template <typename T>
T BST<T>::find(int value)
{
  if(isEmpty())
  {
    cout << "Not found in tree" << endl;
    //return;

  }
  else //look for value
  {
    TreeNode<T> *current = root;

    while(current->key != value) //search for value
    {
      if(current == NULL)
      {
        cout << "Not found in tree" << endl;
        //return;
      }
      if(value < current->key) //go left
        current = current->left;
      else
        current = current->right;
    }
    return current->object;
  }
}

template <typename T>
void BST<T>::deleteRec(int k)
{
  if(!contains(k))
    cout << "Node does not exist" << endl;
  else //find node & delete
  {
    TreeNode<T> *parent = root;
    TreeNode<T> *current = root;
    bool isLeft = true;

    while(current->key != k)
    {
      parent = current;
      if(k < current->key)
      {
        isLeft = true;
        current = current->left;
      }
      else
      {
        isLeft = false;
        current = current->right;
      }
    }

    //found the node we want to delete

    //node has no children (leaf node)
    if(current->left == NULL && current->right == NULL)
    {
      if(current == root)
        root = NULL;
      else if(isLeft)
        parent->left = NULL;
      else
        parent->right = NULL;
    }

    //node has one child
    else if(current->right == NULL) //no right child (must have left child)
    {
      if(current = root)
        root = current->left;
      else if(isLeft)
        parent->left = current->left;
      else //node is right child
        parent->right = current->left;
    }
    else if(current->left == NULL) //no left child (must have right child)
    {
      if(current = root)
        root = current->right;
      else if(isLeft)
        parent->left = current->right;
      else //node is right child
        parent->right = current->right;
    }

    //node has 2 children
    else
    {
      TreeNode<T> *successor = getSuccessor(current);

      if(current == root)
        root = successor;
      else if(isLeft)
        parent->left = successor;
      else
        parent->right = successor;

      successor->left = current->left;
    }
  }
}

template <typename T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T> *d) //d is the node we're deleting
{
  TreeNode<T> *sp = d; //successor's parent
  TreeNode<T> *successor = d; //one right, all the way left
  TreeNode<T> *current = d->right;

  while(current != NULL)
  {
    sp = successor;
    successor = current;
    current = current->left;
  }

  //descendant of right child
  if(successor != d->right)
  {
    sp->left = successor->right;
    successor->right = d->right;
  }

  return successor;
}

// https://www.geeksforgeeks.org/serialize-deserialize-binary-tree/
template <typename T>
void BST<T>::recSerialize(TreeNode<T> *node, ofstream& filename)
{
  if(node == NULL)
  {
    filename << " " << endl;
    return;
  }

  recSerialize(node->left, filename);
  filename << node->object << endl;
  recSerialize(node->right, filename);
}

template <typename T>
void BST<T>::serialize(ofstream& filename)
{
  recSerialize(root, filename);
}

/*
template <typename T>
void BST<T>::recDeserialize(TreeNode<T> *node, ifstream& filename)
{
  // read items from file

  node = TreeNode<T>(o, id);
  recDeserialize(node->left, filename);
  recDeserialize(node->right, filename);
}
*/


#endif
