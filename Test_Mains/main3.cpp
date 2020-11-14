#include "Queue.cpp"

using namespace std;

int main(int argc, char* argv[]) {
  Queue<int>* queue = new Queue<int>();
  for(int i = 0; i < 10; ++i) {
    cout << "PUSHING: " << i << endl;
    queue->push(i);
    queue->printQueue();
    cout << "NEW LENGTH: " << queue->getLength();
  }
  cout << "\n\n";
  for(int i = 0; i < 8; ++i) {
    cout << "Popping: " << queue->pop() << endl;
    queue->printQueue();
    cout << "NEW LENGTH: " << queue->getLength();
  }
  while(!queue->isEmpty()) {
    cout << "Peeking: " << queue->peek() << endl;
    cout << "REMOVING DATA" << endl;
    queue->pop();
    queue->printQueue();
    cout << "NEW LENGTH: " << queue->getLength();
  }
}
