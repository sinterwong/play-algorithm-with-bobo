#include <iostream>
#include "sort_tools.hpp"

template <typename T>
int __partitoin(T arr[], int l, int r)
{
    // 定下一个目标值
    swap(arr[l], arr[rand() % (r - l + 1) + l]);
    T v = arr[l];

    // 初始化维护 <v 的数组的索引
    int j = l;

    // 遍历
    for (size_t i = l + 1; i <= r; i++)
    {
        if (arr[i] < arr[l])
        {
            // 出现小于v的值时，需要放置到由j索引维护的那段数组中
            swap(arr[++j], arr[i]);
        }
    }
    // 最后再将v的位置与j最终的位置进行交换即可达成目的
    swap(arr[l], arr[j]);

    // 返回目标值最终所在的索引
    return j;
}

template <typename T>
int __partitoin2(T arr[], int l, int r)
{
    swap(arr[l], arr[rand() % (r - l + 1) + l])
    T v = arr[l];
    // 目标划分形式：arr[l+1....i), arr(j.....r]
    int i = l + 1;
    int j = r;
    while (true)
    {
        while (i <= r && arr[i] < v)
            i++;
        while (j >= l + 1 && arr[j] > v)
            j--;
        if (i > j)
        {
            break;
        }
        swap(arr[i], arr[j]);
        i++;
        j--;
    }

    swap(arr[l], arr[j]);
    return j;
}

template <typename T>
void __quickSort(T arr[], int l, int r)
{
    srand(time(NULL));
    if (l >= r)
    {
        return;
    }

    int p = __partitoin(arr, l, r);
    __quickSort(arr, l, p - 1);
    __quickSort(arr, p + 1, r);
}

template <typename T>
void quickSort(T arr[], int n)
{
    __quickSort(arr, 0, n - 1);
}

template <typename T>
void __quickSort2(T arr[], int l, int r)
{
    srand(time(NULL));
    if (l >= r)
    {
        return;
    }

    int p = __partitoin2(arr, l, r);
    __quickSort2(arr, l, p - 1);
    __quickSort2(arr, p + 1, r);
}

template <typename T>
void quickSort2(T arr[], int n)
{
    __quickSort2(arr, 0, n - 1);
}

template <typename T>
void __quickSort3(T arr[], int l, int r)
{
    srand(time(NULL));
    if (l >= r)
    {
        return;
    }

    swap(arr[l], arr[rand() % (r - l + 1) + l]);
    T v = arr[l];

    int lt = l;
    int gt = r + 1;
    int i = l + 1;
    while (i < gt)
    {
        if (arr[i] > v)
        {
            swap(arr[i], arr[--gt]);
        }
        else if (arr[i] < v)
        {
            swap(arr[i++], arr[++lt]);
        }
        else
        {
            i++;
        }
    }
    swap(arr[l], arr[lt]);
    __quickSort3(arr, l, lt - 1);
    __quickSort3(arr, gt, r);
}

template <typename T>
void quickSort3(T arr[], int n)
{
    __quickSort3(arr, 0, n - 1);
}

int main(int argc, char const *argv[])
{

    int n = 1000000;
    int *arr1 = SortTestHelper::generateRandomArr(n, 0, n);
    int *arr2 = SortTestHelper::generateNearlyOrderedArr(n, 100);
    int *arr3 = SortTestHelper::generateRandomArr(n, 0, 10);
    // SortTestHelper::testSort("Quick sort", quickSort, arr1, n);
    // SortTestHelper::testSort("Quick sort for nearly ordered", quickSort, arr2, n);
    // SortTestHelper::testSort("Quick sort for repeat data", quickSort, arr3, n);

    int *arr1_2 = SortTestHelper::copyIntArray(arr1, n);
    int *arr2_2 = SortTestHelper::copyIntArray(arr2, n);
    int *arr3_2 = SortTestHelper::copyIntArray(arr3, n);

    int *arr1_3 = SortTestHelper::copyIntArray(arr1, n);
    int *arr2_3 = SortTestHelper::copyIntArray(arr2, n);
    int *arr3_3 = SortTestHelper::copyIntArray(arr3, n);

    // SortTestHelper::testSort("Quick sort1", quickSort, arr1, n);
    // SortTestHelper::testSort("Quick sort1 for nearly ordered", quickSort, arr2, n);
    // SortTestHelper::testSort("Quick sort1 for repeat data", quickSort, arr3, n);

    SortTestHelper::testSort("Quick sort2", quickSort2, arr1_2, n);
    SortTestHelper::testSort("Quick sort2 for nearly ordered", quickSort2, arr2_2, n);
    SortTestHelper::testSort("Quick sort2 for repeat data", quickSort2, arr3_2, n);

    SortTestHelper::testSort("Quick sort3", quickSort3, arr1_3, n);
    SortTestHelper::testSort("Quick sort3 for nearly ordered", quickSort3, arr2_3, n);
    SortTestHelper::testSort("Quick sort3 for repeat data", quickSort3, arr3_3, n);

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr1_2;
    delete[] arr2_2;
    delete[] arr3_2;
    delete[] arr1_3;
    delete[] arr2_3;
    delete[] arr3_3;

    return 0;
}
