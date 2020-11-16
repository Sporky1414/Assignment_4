#include "Student.h"

using namespace std;

class Window {
  public:
    Window();
    ~Window();

    bool isStudentPresent();
    void assignStudent(Student* newStudent);
    Student* studentLeaves();
    int getIdleTime();
    void incrementIdleTime();
    void incrementStudentUseTime();
    bool isStudentFinished();
    void printStudentAtWindow();

  private:
    bool studentPresent;
    int idleTime;
    Student* studentAtWindow;
};
