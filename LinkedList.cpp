#include "LinkedListNode.cpp"

using namespace std;

template <class T>

class LinkedList{
  private:
    LinkedListNode<T>* front;
    LinkedListNode<T>* back;
    unsigned int size;

  public:
    LinkedList();
    ~LinkedList();
    void insertFront(T d);
    void insertBack(T d);
    T removeFront();
    T removeBack();
    int find(T value);
    T deletePos(int pos);
    T removeNode(T key);

    string printList();
    bool isEmpty();
    unsigned int getSize();
};


template <class T>
LinkedList<T>::LinkedList() {
  front = NULL;
  back = NULL;
  size = 0;
}

template <class T>
LinkedList<T>::~LinkedList() {
  for(int i = size; i >= 0; i--) {
    removeBack();
  }
  delete back;
  delete front;
}

template <class T>
void LinkedList<T>::insertFront(T d) {
  LinkedListNode<T> *node = new LinkedListNode<T>(d);
  if(size == 0) {
    back = node;
  } else {
    front->prev = node;
    node->next = front;
  }
  front = node;
  ++size;
}

template <class T>
void LinkedList<T>::insertBack(T d) {
  LinkedListNode<T> *node = new LinkedListNode<T>(d);
  if(size == 0) {
    front = node;
  } else {
    back->next = node;
    node->prev = back;
  }
  back = node;
  ++size;
}

template <class T>
T LinkedList<T>::removeFront() {
  LinkedListNode<T> *node = front;
  if(node == NULL) {
    return T();
  }

  if(front->next == NULL) {
    back = NULL;
  } else {
    //more than one node in the list
    front->next->prev = NULL;
  }
  front = front->next;
  node->next = NULL;
  T temp = node->data;

  size--;
  delete node;

  return temp;
}

template <class T>
T LinkedList<T>::removeBack() {
  LinkedListNode<T> *node = back;
  if(node == NULL) {
    return T();
  }

  if(back->prev == NULL) {
    front = NULL;
  } else {
    //more than one node in List
    back->prev->next = NULL;
  }
  back = back->prev;
  node->prev = NULL;
  T temp = node->data;
  size--;
  delete node;

  return temp;
}

template <class T>
int LinkedList<T>::find(T value) {
  int pos = -1;
  LinkedListNode<T> *curr = front;

  while (curr != NULL) {
    //iterate until we reach the end and hopefully we find what we are looking for
    ++pos;
    if(curr->data == value) {
      break;
    }
    curr = curr->next;
  }

  if(curr == NULL)
    pos = -1;

  return pos;
}

template <class T>
T LinkedList<T>::deletePos(int pos) {
  if(front == NULL) {
    return T();
  }

  int p = 0;
  LinkedListNode<T> *curr = front;
  LinkedListNode<T> *prev = front;

  while(p != pos) {
    prev = curr;
    curr = curr->next;
    p++;
  }

  //if I make it here, found node that contiains the key.

  if(curr == front) {
    front = curr->next;
    front->prev = NULL;
  } else if (curr == back) {
    back = curr->prev;
    back->next = NULL;
  } else {
    //it's between front and back
    prev->next = curr->next;
    prev->next->prev = curr->prev;
  }

  curr->next = NULL;
  curr->prev = NULL;

  T temp = curr->data;
  size--;

  delete curr;
  return temp;
}

template <class T>
T LinkedList<T>::removeNode(T key) {
  LinkedListNode<T> *curr = front;

  if(curr == NULL) {
    return T();
  }

  //if not empty, you can leverage find() to determine if value even exists

  while(curr->data != key) {
    curr = curr->next;

    if(curr == NULL) {
      //I reached the end of my linked list and did not find the key/value
      return T();
    }
  }

  //if I make it here, found node that contiains the key.

  if(curr == front) {
    front = curr->next;
    front->prev = NULL;
  } else if (curr == back) {
    back = curr->prev;
    back->next = NULL;
  } else {
    //it's between front and back
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
  }

  curr->next = NULL;
  curr->prev = NULL;

  T temp = curr->data;
  size--;
  delete curr;

  return temp;
}

template <class T>
string LinkedList<T>::printList() {
  string returnString = "";
  LinkedListNode<T> *curr = front;
  while(curr != NULL) {
    returnString += "\"" + to_string(curr->data) + "\"";
    curr = curr->next;
    if(curr != NULL) {
      returnString += ", ";
    } else {
      returnString +=". ";
    }
  }
  returnString += "SIZE: " + to_string(getSize());
  delete curr;
  return returnString;
}

template <class T>
bool LinkedList<T>::isEmpty() {
  return size <= 0;
}

template <class T>
unsigned int LinkedList<T>::getSize() {
  return size;
}
