#include <iostream>
#include "sort_tools.hpp"

template <typename T>
void insertionSort(T arr[], int n)
{
    for (size_t i = 1; i < n; i++)
    {
        for (size_t j = i; j > 0 && arr[j] < arr[j - 1]; j--)
        {
            swap(arr[j], arr[j - 1]);
        }
    }
}

template <typename T>
void insertionSort2(T arr[], int n)
{
    for (size_t i = 1; i < n; i++)
    {
        T temp = arr[i];
        size_t j;
        for (j = i; j > 0 && temp < arr[j - 1]; j--)
        {
            arr[j] = arr[j - 1];
        }
        arr[j] = temp;
    }
}
