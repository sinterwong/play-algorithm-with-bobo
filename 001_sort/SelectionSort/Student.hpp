#ifndef __TEST_STUDENT_H
#define __TEST_STUDENT_H

#include <iostream>
using namespace std;

class Student
{
public:
    explicit Student() {}
    explicit Student(string name, float score) : name(name), score(score) {}

public:
    string name;
    float score;

public:
    bool operator<(const Student &otherStudent);

    friend ostream &operator<<(ostream &os, const Student &student)
    {
        os << "Student: " << student.name << " " << student.score << endl;
        return os;
    }
};

#endif // __TEST_STUDENT_H