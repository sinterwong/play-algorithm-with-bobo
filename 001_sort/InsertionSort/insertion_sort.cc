#include <iostream>
#include "sort_tools.hpp"

template <typename T>
void insertionSorted(T arr[], int n)
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
void insertionSorted2(T arr[], int n)
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

int main(int argc, char const *argv[])
{
    int n = 10000;
    int *arr1 = SortTestHelper::generateRandomArr(n, 0, n);
    int *arr2 = SortTestHelper::copyIntArray(arr1, n);
    int *arr3 = SortTestHelper::generateNearlyOrderedArr(n, 100);
    SortTestHelper::testSort("Insertion sort", insertionSorted, arr1, n);
    SortTestHelper::testSort("Insertion sort2", insertionSorted2, arr2, n);
    SortTestHelper::testSort("Insertion sort2 for nearly ordered array", insertionSorted2, arr3, n);
    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    return 0;
}
