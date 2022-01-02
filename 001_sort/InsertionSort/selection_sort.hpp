#include <iostream>
#include "sort_tools.hpp"
#include "Student.hpp"

using namespace std;

template <typename T>
void selectionSorted(T arr[], int n)
{
    for (size_t i = 0; i < n; i++)
    {
        int minIndex = i;
        for (size_t j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

