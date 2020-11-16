#include "Window.h"

Window::Window() {
  studentPresent = false;
  studentAtWindow = NULL;
  idleTime = 0;
}

Window::~Window() {
  //Not deleting student should the window be deleted, since that could cause problems elsewhere.
}

bool Window::isStudentPresent() {
  return studentPresent;
}

void Window::assignStudent(Student* newStudent) {
  studentAtWindow = newStudent;
  studentPresent = true;
}

Student* Window::studentLeaves() {
  Student* temp = studentAtWindow;
  studentAtWindow = NULL;
  studentPresent = false;
  return temp;
}

int Window::getIdleTime() {
  return idleTime;
}

void Window::incrementIdleTime() {
  ++idleTime;
}

void Window::incrementStudentUseTime() {
  studentAtWindow->incrementClockTicksAtWindow();
}

bool Window::isStudentFinished() {
  return studentAtWindow->isFinishedAtWindow();
}

void Window::printStudentAtWindow() {
  cout << to_string(*studentAtWindow);
}
