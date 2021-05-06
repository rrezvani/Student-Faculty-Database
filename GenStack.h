#ifndef GEN_STACK_H
#define GEN_STACK_H

#include <iostream>

using namespace std;

template <typename T>
class GenStack{
  public:
      GenStack();
      GenStack(int maxSize);
      ~GenStack();

      void push(T data);
      T pop();
      T peek();

      bool isFull();
      bool isEmpty();
      int getSize();

  private:
    int top;
    int mSize;
    T *myArray;

    void rebuild();
};

template <typename T>
GenStack<T>::GenStack(){
  myArray = new T[128];
  mSize = 128;
  top = -1;
}

template <typename T>
GenStack<T>::GenStack(int maxSize) {
  myArray = new T[maxSize];
  mSize = maxSize;
  top = -1;
}

template <typename T>
GenStack<T>::~GenStack(){
  delete [] myArray;
}

template <typename T>
void GenStack<T>::push(T data){
  if (isFull()) {
    rebuild();
  }
  myArray[++top] = data;
}

template <typename T>
void GenStack<T>::rebuild(){
  int oldSize = mSize;
  mSize = mSize*2;
  T *newArray = new T[mSize];
  for (int i = 0; i < oldSize; ++i) {
    newArray[i] = myArray[i];
  }
  myArray = newArray;
}

template <typename T>
T GenStack<T>::pop(){
  if(isEmpty()){
    throw invalid_argument("You can't delete from an empty stack!");
  } else {
    return myArray[top--];

  }
}

template <typename T>
T GenStack<T>::peek(){
    return myArray[top];
}

template <typename T>
bool GenStack<T>::isFull(){
  return (top == mSize-1);
}

template <typename T>
bool GenStack<T>::isEmpty(){
  return (top == -1);
}

template <typename T>
int GenStack<T>::getSize(){
  return (top + 1);
}

#endif
