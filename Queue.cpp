/*
  Name: AJ Keenan
  Student ID: 2316808
  Class Name: CPSC 350: Data Structures and Algorithms
  Class Section: 2
  Assignment Name: Assignment 4
*/

#include "LinkedList.cpp"

using namespace std;

template <class T>

//A template class that implements the Queue abstract data type using a linked list as the underlying data structure
class Queue {
  public:
    //Constructor and destructor. No special cases for a queue constructor/destructor required.
    Queue();
    ~Queue();

    //Adds data to the back of the queue
    void push(T data);
    //Deletes the data from the front of the queue and returns it.
    T pop();
    //Returns a copy of the data currently stored at the front of the queue.
    T peek();

    //Checks if the queue is empty.
    bool isEmpty();
    //Returns the current length of the queue.
    unsigned int getLength();
    //Prints out the queue.
    void printQueue();

  private:
    //The underlying List ADT (which will be of type LinkedList) to hold the queue data.
    ListADT<T>* queue;
};

//Constructor: Initializes an empty LinkedList as the queue backbone.
template <class T>
Queue<T>::Queue() {
  queue = new LinkedList<T>();
}

//Deletes the linked list queue and all data stored inside (should any be present)
template <class T>
Queue<T>::~Queue() {
  delete queue;
}

//Adds data to the back of the queue.
template <class T>
void Queue<T>::push(T data) {
  queue->append(data);
}

//Removes the piece of data at the front of the queue and returns it.
template <class T>
T Queue<T>::pop() {
  T temp = queue->remove(queue->valueAt(0));
  return temp;
}

//Returns a copy of the data at the front of the queue.
template <class T>
T Queue<T>::peek() {
  return queue->valueAt(0);
}

//Returns if the queue is empty, or has a length of 0.
template <class T>
bool Queue<T>::isEmpty() {
  return getLength() == 0;
}

//Returns the current length of the queue.
template <class T>
unsigned int Queue<T>::getLength() {
  return queue->getLength();
}

//Prints out the queue data.
template <class T>
void Queue<T>::printQueue() {
  queue->print();
}
