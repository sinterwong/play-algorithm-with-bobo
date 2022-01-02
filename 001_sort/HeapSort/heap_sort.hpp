#ifndef __HEAP_SORT_H
#define __HEAP_SORT_H

#include "heap.hpp"

template <typename T>
void __shiftDown(T arr[], int n, int k)
{
    while (k * 2 + 1 < n)
    {
        int j = k * 2 + 1;
        if (j + 1 < n && arr[j] < arr[j + 1])
        {
            j++;
        }
        if (arr[j] <= arr[k])
        {
            break;
        }
        swap(arr[j], arr[k]);
        k = j;
    }
}

template <typename T>
void heapSort(T arr[], int n)
{
    for (int i = (n - 1) / 2; i >= 0; i--)
    {
        __shiftDown(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[i], arr[0]);
        __shiftDown(arr, i, 0);
    }
}

template <typename T>
void heapSort1(T arr[], int n)
{
    MaxHeap<T> maxHeap = MaxHeap<T>(n);
    for (size_t i = 0; i < n; i++)
    {
        maxHeap.insert(arr[i]);
    }

    for (int i = n - 1; i >= 0; i--)
    {
        arr[i] = maxHeap.extractMax();
    }
}

template <typename T>
void heapSort2(T arr[], int n)
{
    MaxHeap<T> maxHeap = MaxHeap<T>(arr, n);
    for (int i = n - 1; i >= 0; i--)
    {
        arr[i] = maxHeap.extractMax();
    }
}

#endif // __HEAP_SORT_H