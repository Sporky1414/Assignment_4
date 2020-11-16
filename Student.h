#include <iostream>
#include <fstream>

using namespace std;

class Student {
  public:
    Student();
    Student(int timeNeeded);
    ~Student();

    void incrementWaitTime();
    void incrementClockTicksAtWindow();
    int getWaitTime();
    int getClockTicksUsed();
    int getClockTicksNeeded();
    bool isAtWindow();
    bool isFinishedAtWindow();
    void goToWindow();
    void leaveWindow();

    friend ostream &operator<<(ostream &out, Student &student);
    friend string to_string(Student &student);
    bool operator ==(const Student& otherStudent);
    bool operator <(const Student& otherStudent);
    bool operator >(const Student& otherStudent);

  private:
    int waitTime;
    int clockTicksUsed;
    int clockTicksNeeded;
    bool atWindow;
};
