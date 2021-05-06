#ifndef BST_H
#define BST_H

#include <iostream>
#include "Student.h"

using namespace std;

template <typename T>
class TreeNode {
  public:
    TreeNode();
    TreeNode(T data);
    //TreeNode(int data, object value);
    ~TreeNode();

    T key;
    TreeNode *left;
    TreeNode *right;
};

template <typename T>
TreeNode<T>::TreeNode() {
  left = NULL;
  right = NULL;
}

template <typename T>
TreeNode<T>::TreeNode(T data) {
  key = data;
  left = NULL;
  right = NULL;
}

template <typename T>
TreeNode<T>::~TreeNode() {
  left = NULL;
  right = NULL;
  //build some character
}

template <typename T>
class BST {
  public:
    BST();
    ~BST();
    void insert(T value);
    void recPrintStudent(TreeNode<T> *node);
    void recPrintFaculty(TreeNode<T> *node);
    void destroyTree(TreeNode<T> *node);
    bool contains(T value); //this is search
    void deleteNode(T k);
    bool isEmpty();
    T getMin(); //for a template class, return T*
    T getMax();
    T getNode(int value);
    TreeNode<T>* getSuccesor(TreeNode<T> *d); //this function plays a large role in deleteNode()
    TreeNode<T>* getRoot();
    TreeNode<T>* getTreeNode(int value);

  private:
    TreeNode<T> *root;
};

template <typename T>
BST<T>::BST() {
  root = NULL; //empty tree
}

template <typename T>
BST<T>::~BST() {
  destroyTree(root);
  //build some character
}

template <typename T>
void BST<T>::recPrintStudent(TreeNode<T> *node) { //function that prints all the students in order
  if (node == NULL) {
    return;
  }
  recPrintStudent(node->left);
  node->key.printMe();
  recPrintStudent(node->right);
}

template <typename T>
void BST<T>::recPrintFaculty(TreeNode<T> *node) { //function that prints all the faculty in order
  if (node == NULL) {
    return;
  }
  recPrintFaculty(node->left);
  node->key.printMe();
  recPrintFaculty(node->right);
}

template <typename T>
T BST<T>::getMin() {
  if (root == NULL) {
    return 0;
  }
  TreeNode<T> *current = root; //we always start at the root
  while (current->left != NULL) {
    current = current->left;
  }

  return current->key;
}

template <typename T>
T BST<T>::getMax() {
  if (root == NULL) {
    return 0;
  }
  TreeNode<T> *current = root; //we always start at the root
  while (current->right != NULL) {
    current = current->right;
  }

  return current->key;
}

template <typename T>
void BST<T>::insert(T value) {
  TreeNode<T> *node = new TreeNode<T>(value);

  if (isEmpty()) {
    root = node;
  }
  else {
    //the tree is not empty, need to find the insertion point
    TreeNode<T> *current = root;
    TreeNode<T> *parent = NULL;

    while (true) {
      parent = current;

      if (value < current->key) {
        current = current->left;

        if (current == NULL) {
          // we found our insertion point
          parent->left = node;
          break;
        }
      }
      else {
        current = current->right;

        if (current == NULL) {
          parent->right = node;
          break;
        }
      }
    }
  }
}

template <typename T>
bool BST<T>::contains(T value) {
  if (isEmpty()) {
    return false;
  }
  else {
    //if it's not empty, let's go find the node
    TreeNode<T> *current = root;

    while (current->key != value) {
      if (value < current->key) {
        current = current->left;
      }
      else {
        current = current->right;
      }

      if (current == NULL) {
        return false;
      }
    }
  }
  return true;
}

template <typename T>
void BST<T>::deleteNode(T k) {
  if (isEmpty()) {
    cout << "Cannot delete because tree is empty" << endl;
  }

  TreeNode<T> *parent = NULL;
  TreeNode<T> *current = root;
  bool isLeftNode = true;

  while (current->key != k) {
    parent = current;

    if (k < current->key) {
      isLeftNode = true;
      current = current->left;
    }
    else {
      isLeftNode = false;
      current = current->right;
    }

    if (current == NULL) {
      cout << "Could not find node" << endl;
    }
  }
  // at this point, we have our key/value, now we have to delete the node

  //case: node to be deleted is a leaf node (no children)
  if (current->left == NULL && current->right == NULL) {
    if (current == root) {
      root = NULL;
    }
    else if (isLeftNode) {
      parent->left = NULL;
    }
    else {
      parent->right = NULL;
    }
  }

  //case: node to be deleted has only one child, need to determine whether descendant is left or right
  else if (current->right == NULL) {
    //means there is a left node, but no right node. the node is a left child
    if (current == root) {
      root = current->left;
    }
    else if (isLeftNode) {
      parent->left = current->left;
    }
    else {
      //node to be deleted is a right child
      parent->right = current->left;
    }
  }

  else if (current->left == NULL) {
    //means there is a right node, but no left node. the node is a right child
    if (current == root) {
      root = current->right;
    }
    else if (isLeftNode) {
      parent->left = current->right;
    }
    else {
      //node to be deleted is a right child
      parent->right = current->right;
    }
  }

  else {
    //the node to be deleted has two children, at this point we begin to cry
    //we have to find the succesor (AIDS)
    TreeNode<T> *succesor = getSuccesor(current); //current is the node to be defined
    if (current == root) {
      root = succesor;
    }
    else if (isLeftNode) {
      parent->left = succesor;
    }
    else {
      parent->right = succesor;
    }
    succesor->left = current->left;
  }
}

template <typename T>
TreeNode<T>* BST<T>::getSuccesor(TreeNode<T> *d) {
  TreeNode<T> *sp = d;
  TreeNode<T> *s = d;
  TreeNode<T> *current = d->right;

  while (current != NULL) {
    sp = s;
    s = current;
    current = current->left;
  }

  if (s != d->right) {
    sp->left = s->right;
    s->right = d->right;
  }
  return s;
}

template <typename T>
bool BST<T>::isEmpty() {
  return (root == NULL);
}

template <typename T>
TreeNode<T>* BST<T>::getRoot() { //my own function that returns the root
  return root;
}

template <typename T>
T BST<T>::getNode(int value) { //my own function that returns the type (either faculty or student) of node given the ID
  TreeNode<T> *current = root;
  if (isEmpty()) {
    cout << "Empty tree" << endl;
  }
  else {
    //if it's not empty, let's go find the node

    while (current->key.ID != value) {
      if (value < current->key.ID) {
        current = current->left;
      }
      else {
        current = current->right;
      }

      if (current == NULL) {
        cout << "Node not found" << endl;
        return 0;
      }
    }
  }
  return current->key;
}

template <typename T>
TreeNode<T>* BST<T>::getTreeNode(int value) { //same thing as above but returned as a TreeNode instead
  TreeNode<T> *current = root;
  if (isEmpty()) {
    cout << "Empty tree" << endl;
  }
  else {
    //if it's not empty, let's go find the node

    while (current->key.ID != value) {
      if (value < current->key.ID) {
        current = current->left;
      }
      else {
        current = current->right;
      }

      if (current == NULL) {
        cout << "Node not found" << endl;
        return 0;
      }
    }
  }
  return current;
}

template <typename T>
void BST<T>::destroyTree(TreeNode<T> *node) { //destructor for BST
  if (node)
  {
      destroyTree(node->left);
      destroyTree(node->right);
      delete node;
  }
}


#endif
