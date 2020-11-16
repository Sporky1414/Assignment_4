#include "Student.h"
#include <sstream>

Student::Student() {
  waitTime = 0;
  clockTicksUsed = 0;
  clockTicksNeeded = 0;
  atWindow = false;
}

Student::Student(int timeNeeded) {
  waitTime = 0;
  clockTicksUsed = 0;
  clockTicksNeeded = timeNeeded;
  atWindow = false;
}

Student::~Student() {}

void Student::incrementWaitTime() {
  ++waitTime;
}

void Student::incrementClockTicksAtWindow() {
  ++clockTicksUsed;
}

int Student::getWaitTime() {
  return waitTime;
}

int Student::getClockTicksUsed() {
  return clockTicksUsed;
}

int Student::getClockTicksNeeded() {
  return clockTicksNeeded;
}

bool Student::isAtWindow() {
  return atWindow;
}

bool Student::isFinishedAtWindow() {
  return clockTicksUsed == clockTicksNeeded;
}

void Student::goToWindow() {
  atWindow = true;
}

void Student::leaveWindow() {
  atWindow = false;
}

ostream& operator<<(ostream &out, Student &student) {
  out << "Wait Time: " << to_string(student.getWaitTime()) << "\nClockTicksUsed: " << to_string(student.getClockTicksUsed()) << "\nClockTicksNeeded: " << to_string(student.getClockTicksNeeded()) << endl;
  return out;
}

string to_string(Student &student) {
  ostringstream ss;
  ss << student;
  return ss.str();
}

bool Student::operator ==(const Student& otherStudent) {
  return (waitTime == otherStudent.waitTime && clockTicksUsed == otherStudent.clockTicksUsed && clockTicksNeeded == otherStudent.clockTicksNeeded);
}

bool Student::operator <(const Student& otherStudent) {
  return waitTime + clockTicksUsed + clockTicksNeeded < otherStudent.waitTime + otherStudent.clockTicksUsed + otherStudent.clockTicksNeeded;
}

bool Student::operator >(const Student& otherStudent) {
  return waitTime + clockTicksUsed + clockTicksNeeded > otherStudent.waitTime + otherStudent.clockTicksUsed + otherStudent.clockTicksNeeded;
}
