#include "LinkedListNode.cpp"
#include "ListADT.h"

using namespace std;

template <class T>

//A template class implementing the Linked List data structure, with it being subclass of the ListADT.
class LinkedList: public ListADT<T> {
  private:
    //Pointer nodes to the front and back nodes of the linked list.
    LinkedListNode<T>* front;
    LinkedListNode<T>* back;
    //Integer value of how many nodes are present in the list.
    unsigned int length;

    //Removes the front and back nodes from the Linked List.
    T removeFront();
    T removeBack();

  public:
    //Constructor/Destructor for the LinkedList.
    LinkedList();
    ~LinkedList();

    //Adds the given data to the front of the list.
    void prepend(T data);
    //Adds the given data to the back of the list.
    void append(T data);
    //Adds the new data after the given datapoint.
    void insertAfter(T newData, T datapointItemBeingAddedAfter);
    //Removes the given data from the linked list.
    T remove(T data);

    //Returns the position currently storing the given data.
    int searchFor(T value);
    //Returns the data stored at the given position of the linked list.
    T valueAt(int pos);

    //Prints the linked list data.
    void print();
    //Prints the linked list data, but in reverse.
    void printReverse();

    //Returns if the linked list is empty (or length == 0)
    bool isEmpty();
    //Returns the value of length.
    unsigned int getLength();

    //Sorts the data of the linked list.
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
