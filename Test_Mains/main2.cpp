#include "LinkedList.cpp"

using namespace std;

int main(int argc, char* argv[]) {
  ListADT<int> *list = new LinkedList<int>();
  for(int i = 0; i < 5; ++i) {
    list->append(i);
    list->print();
  }
  cout << "\n\n";

  for(int i = 134; i > 129; i--) {
    list->prepend(i);
    list->print();
  }
  cout << "\n\n";

  list->print();
  list->printReverse();

  cout << "\n\n";
  for(int i = 11; i < 16; ++i) {
    list->insertAfter(i, i - 10);
    list->print();
  }
  cout << "\n\n";

  list->print();
  list->sortSelf();
  list->print();
  cout << "\n\n";

  list->print();
  cout << "Pos of 13: " << to_string(list->searchFor(13)) << endl;
  list->remove(13);
  list->print();
  int dataIn6 = list->valueAt(6);
  cout << "Data in index 6: " << to_string(dataIn6) << endl;
  list->remove(dataIn6);
  list->print();
  cout<< "Pos of 24: " << to_string(list->searchFor(24)) << endl;
  cout << "Data in Index 2: " << to_string(list->valueAt(2)) << endl;
  cout << "\n\n";

  while(!list->isEmpty()) {
    list->remove(0);
    list->print();
    if(!list->isEmpty()) {
      list->remove(list->getLength() - 1);
      list->print();
    }
    if(!list->isEmpty()) {
      list->remove(list->getLength()/2);
      list->print();
    }
  }
}
