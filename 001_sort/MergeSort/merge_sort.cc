#include <iostream>
#include "sort_tools.hpp"

using namespace std;

template <typename T>
void __merge(T arr[], int l, int mid, int r)
{
    T aux[r - l + 1];
    // 将当前段的elements赋值到辅助数组中
    for (size_t i = l; i <= r; i++)
    {
        aux[i - l] = arr[i];
    }

    int i = l;
    int j = mid + 1;
    for (size_t k = l; k <= r; k++)
    {
        if (i > mid)
        {
            arr[k] = aux[j - l];
            j++;
        }
        else if (j > r)
        {
            arr[k] = aux[i - l];
            i++;
        }
        else if (aux[i - l] < aux[j - l])
        {
            arr[k] = aux[i - l];
            i++;
        }
        else
        {
            arr[k] = aux[j - l];
            j++;
        }
    }
}

template <typename T>
void __mergeSort(T arr[], int l, int r)
{
    if (l >= r) // 由于每次拆分左侧为r折半，右侧为l+1，因此当l>=r是意味着已经拆分到只剩1个或0个，无法继续拆分
    {
        return;
    }
    int mid = (l + r) / 2;
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid + 1, r);
    if (arr[mid] > arr[mid + 1]) // 如果左边最大小于右边最小，则不需要归并。该操作对于相对有序的数据会大大提速
    {
        __merge(arr, l, mid, r);
    }
}


template <typename T>
void mergeSorted(T arr[], int n)
{
    __mergeSort(arr, 0, n - 1);
}


template <typename T>
void mergeSortedBU(T arr[], int n)
{
    // 第一次循环数为整个归并划分的level数，也就是 log(i)次
    for (int i = 1; i < n; i+=i)
    {
        // 实现当前level下的每一次归并，每次迭代
        for (int j = 0; j+i < n; j+=i+i)
        {
            __merge(arr, j, j+i-1, min(j+i+i-1, n-1));
        }
    }
    
}


int main(int argc, char const *argv[])
{
    int n = 1000000;
    int *arr1 = SortTestHelper::generateRandomArr(n, 0, n);
    int *arr2 = SortTestHelper::generateNearlyOrderedArr(n, 100);
    int *arr1_2 = SortTestHelper::copyIntArray(arr1, n);
    int *arr2_2 = SortTestHelper::copyIntArray(arr2, n);
    SortTestHelper::testSort("Merge sort", mergeSorted, arr1, n);
    SortTestHelper::testSort("Merge sort for nearly ordered", mergeSorted, arr2, n);
    SortTestHelper::testSort("Merge sort BU", mergeSortedBU, arr1_2, n);
    SortTestHelper::testSort("Merge sort BU for nearly ordered", mergeSortedBU, arr2_2, n);
    delete[] arr1;
    delete[] arr2;
    delete[] arr1_2;
    delete[] arr2_2;
    return 0;
}
