#include <iostream>

using namespace std;

template <class T>
class LinkedListNode {
  public:
    LinkedListNode();
    LinkedListNode(T newData);
    ~LinkedListNode();

    LinkedListNode<T>* next;
    LinkedListNode<T>* prev;
    T data;
};

template <class T>
LinkedListNode<T>::LinkedListNode() {
  next = NULL;
  prev = NULL;
  data = NULL;
}

template <class T>
LinkedListNode<T>::LinkedListNode(T newData) {
  next = NULL;
  prev = NULL;
  data = newData;
}

template <class T>
LinkedListNode<T>::~LinkedListNode() {
  next = NULL;
  prev = NULL;
  delete next;
  delete prev;
}
