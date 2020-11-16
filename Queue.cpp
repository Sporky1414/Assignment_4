#include "LinkedList.cpp"

using namespace std;

template <class T>

class Queue {
  public:
    Queue();
    ~Queue();
    void push(T data);
    T pop();
    T peek();
    bool isEmpty();
    unsigned int getLength();
    void printQueue();

  private:
    ListADT<T>* queue;
};

template <class T>
Queue<T>::Queue() {
  queue = new LinkedList<T>();
}

template <class T>
Queue<T>::~Queue() {
  delete queue;
}

template <class T>
void Queue<T>::push(T data) {
  queue->append(data);
}

template <class T>
T Queue<T>::pop() {
  T temp = queue->remove(queue->valueAt(0));
  return temp;
}

template <class T>
T Queue<T>::peek() {
  return queue->valueAt(0);
}

template <class T>
bool Queue<T>::isEmpty() {
  return getLength() == 0;
}

template <class T>
unsigned int Queue<T>::getLength() {
  return queue->getLength();
}

template <class T>
void Queue<T>::printQueue() {
  queue->print();
}
