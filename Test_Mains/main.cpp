#include "LinkedList.cpp"

using namespace std;

int main(int argc, char* argv[]) {
  LinkedList<int>* list = new LinkedList<int>();
  for(int i = 0; i < 10; ++i) {
    list->insertFront(i);
    cout << list->printList() << endl;
  }
  cout << "\n\n";

  for(int i = 100; i > 90; i--) {
    list->insertBack(i);
    cout << list->printList() << endl;
  }
  cout <<"\n\n";

  for(int i = 0; i < 5; ++i) {
    list->removeFront();
    cout << list->printList() << endl;
  }
  cout <<"\n\n";

  cout << list->printList() << endl;
  int temp = list->find(95);
  cout << "Pos of 95: " << to_string(temp) << endl;
  list->deletePos(temp);
  cout << list->printList() << endl;
  cout << "Pos of 99: " << to_string(list->find(99)) << endl;
  list->removeNode(99);
  cout << list->printList() << endl;
  cout << "Pos of 101: " << list->find(101) << endl;

  cout << "\n\n";

  ///segmentation fault here
  while(!list->isEmpty()) {
    list->removeBack();
    cout << list->printList() << endl;
  }

  cout << "Is list empty?: " << to_string(list->isEmpty()) << endl;

  delete list;
  return 0;
}
