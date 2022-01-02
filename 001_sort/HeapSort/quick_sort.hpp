#ifndef __QUICK_SORT_H
#define __QUICK_SORT_H

#include <iostream>
using namespace std;

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
    swap(arr[l], arr[rand() % (r - l + 1) + l]);
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

#endif // __QUICK_SORT_H