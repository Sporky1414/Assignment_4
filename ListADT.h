using namespace std;

template <class T>

class ListADT {
  public:
    virtual void append(T data) = 0;
    virtual void prepend(T data) = 0;
    virtual void insertAfter(T newData, T datapointItemBeingAddedAfter) = 0;
    virtual T remove(T data) = 0;
    virtual int searchFor(T data) = 0;
    virtual T valueAt(int pos) = 0;
    virtual void print() = 0;
    virtual void printReverse() = 0;
    virtual void sortSelf() = 0;
    virtual bool isEmpty() = 0;
    virtual unsigned int getLength() = 0;
};
