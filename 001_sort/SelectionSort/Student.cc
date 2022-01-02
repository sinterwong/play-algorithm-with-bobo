#include "Student.hpp"

bool Student::operator<(const Student &otherStudent)
{
    return score != otherStudent.score ? score < otherStudent.score : name < otherStudent.name;
}
