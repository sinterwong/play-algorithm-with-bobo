#ifndef __SORT_TOOLS_H
#define __SORT_TOOLS_H
#include <iostream>
#include <assert.h>

using namespace std;
namespace SortTestHelper
{
    // Generator of random array
    int *generateRandomArr(int n, int rangeL, int rangeR)
    {
        srand(time(NULL));     // 设置时间戳作为随机种子
        int *arr = new int[n]; // new会创建一个指针
        for (size_t i = 0; i < n; i++)
        {
            // rand会创建一个随机的整数，取模之后获取[0, rangeL], 再加上一个偏移量
            arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
        }

        return arr;
    }

    // Generator of random array
    int *generateNearlyOrderedArr(int n, int swapTimes)
    {
        int *arr = new int[n];
        
        for (size_t i = 0; i < n; i++)
        {
            arr[i] = i;
        }

        srand(time(NULL));
        for (size_t i = 0; i < swapTimes; i++)
        {
            int posx = rand() % n;  // [0, n)            
            int posy = rand() % n;  // [0, n)

            swap(arr[posx], arr[posy]);            
        }
        return arr;
    }

    // Print array
    template <typename T>
    void printArray(T arr[], int n)
    {
        for (size_t i = 0; i < n; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    // Whether the result are correct
    template <typename T>
    bool isSorted(T arr[], int n)
    {
        for (size_t i = 0; i < n-1; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                return false;
            }
        }
        return true;
    }

    // Copy array
    int *copyIntArray(int a[], int n)
    {
        int *arr = new int[n];
        copy(a, a + n, arr);
        return arr;
    }

    // Test speed for the sorting algorithm
    template <typename T>
    void testSort(const string &name, void (*sort)(T[], int), T arr[], int n)
    {
        clock_t start = clock();
        sort(arr, n);
        clock_t end = clock();
        assert(isSorted(arr, n)); // 校验结果
        cout << name << " : " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;
    }
}

#endif // __SORT_TOOLS_H