#include "LinkedListNode.cpp"
#include "ListADT.h"

using namespace std;

template <class T>

class LinkedList: public ListADT<T> {
  private:
    LinkedListNode<T>* front;
    LinkedListNode<T>* back;
    unsigned int length;

    T removeFront();
    T removeBack();

  public:
    LinkedList();
    ~LinkedList();
    void prepend(T data);
    void append(T data);
    void insertAfter(T newData, T datapointItemBeingAddedAfter);
    T remove(T data);
    int searchFor(T value);
    T valueAt(int pos);

    void print();
    bool isEmpty();
    unsigned int getLength();

    void printReverse();
    void sortSelf();
};


template <class T>
LinkedList<T>::LinkedList() {
  front = NULL;
  back = NULL;
  length = 0;
}

template <class T>
LinkedList<T>::~LinkedList() {
  for(int i = length; i >= 0; i--) {
    removeBack();
  }
  delete back;
  delete front;
}

template <class T>
void LinkedList<T>::prepend(T d) {
  LinkedListNode<T> *node = new LinkedListNode<T>(d);
  if(getLength() == 0) {
    front = node;
    back = node;
  } else {
    front->prev = node;
    node->next = front;
  }
  front = node;
  ++length;
}

template <class T>
void LinkedList<T>::append(T d) {
  LinkedListNode<T> *node = new LinkedListNode<T>(d);
  if(getLength() == 0) {
    front = node;
    back = node;
  } else {
    back->next = node;
    node->prev = back;
  }
  back = node;
  ++length;
}

template <class T>
void LinkedList<T>::insertAfter(T d, T datapointItemBeingAddedAfter) {
  int pos = this->searchFor(datapointItemBeingAddedAfter);
  if(pos == 0) {
    prepend(d);
    return;
  } else if (pos >= length - 1) {
    append(d);
    return;
  } else if (pos == -1) {
    cout <<"INVALID POSITION ENTERED. INSERTING DATA AT BACK" << endl;
    append(d);
    return;
  }
  LinkedListNode<T>* newNode = new LinkedListNode<T>(d);
  int p = 0;

  LinkedListNode<T>* curr = front;
  LinkedListNode<T>* succ = front->next;

  while(p != pos) {
    curr = curr->next;
    ++p;
  }
  succ = curr->next;

  newNode->next = succ;
  newNode->prev = curr;
  curr->next = newNode;
  succ->prev = newNode;
  ++length;
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

  length--;
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
  length--;
  delete node;

  return temp;
}

template <class T>
T LinkedList<T>::remove(T data) {
  int pos = searchFor(data);
  LinkedListNode<T>* curr = front;
  for(int i = 0; i < pos; ++i) {
    curr = curr->next;
  }
  LinkedListNode<T>* sucNode = curr->next;
  LinkedListNode<T>* predNode = curr->prev;
  if(sucNode != NULL) {
    sucNode->prev = predNode;
  }
  if(predNode != NULL) {
    predNode->next = sucNode;
  }
  if(curr == front) {
    front = sucNode;
  }
  if(curr == back) {
    back = predNode;
  }
  length--;
  T temp = curr->data;
  delete curr;
  return temp;
}

template <class T>
int LinkedList<T>::searchFor(T value) {
  int pos = -1;
  LinkedListNode<T> *curr = front;

  while (curr != NULL) {
    //iterate until we reach the end and hopefully we searchFor what we are looking for
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
T LinkedList<T>::valueAt(int pos) {
  LinkedListNode<T> *curr = front;

  for(int i = 0; i < pos; ++i) {
    curr = curr->next;
  }
  return curr->data;
}

template <class T>
void LinkedList<T>::print() {
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
  delete curr;
  cout << returnString << endl;
}

template <class T>
void LinkedList<T>::printReverse() {
  string returnString = "";
  LinkedListNode<T> *curr = back;
  while(curr != NULL) {
    returnString += "\"" + to_string(curr->data) + "\"";
    curr = curr->prev;
    if(curr != NULL) {
      returnString += ", ";
    } else {
      returnString +=". ";
    }
  }
  delete curr;
  cout << returnString << endl;
}

template <class T>
void LinkedList<T>::sortSelf() {
  T min = front->data;
  LinkedList<T> *newList = new LinkedList<T>();
  LinkedListNode<T> *curr = front;
  while(front != NULL) {
    while(curr != NULL) {
      if(min > curr->data) {
        min = curr->data;
      }
      curr = curr->next;
    }
    remove(min);
    newList->append(min);
    if(front != NULL) {
      min = front->data;
      curr = front;
    }
  }
  newList->print();
  curr = newList->front;
  while(curr != NULL) {
    append(curr->data);
    curr = curr->next;
  }
  delete curr;
  delete newList;
}

template <class T>
bool LinkedList<T>::isEmpty() {
  return length <= 0;
}

template <class T>
unsigned int LinkedList<T>::getLength() {
  return length;
}
