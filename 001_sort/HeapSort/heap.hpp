#ifndef __HEAP_H
#define __HEAP_H

#include <algorithm>
#include <string>
#include <ctime>
#include <cmath>
#include <cassert>

#include <iostream>
using namespace std;

template <typename Item>
class MaxHeap
{
private:
    Item *data;   // heap data
    int count;    // data count
    int capacity; // capacity of heap

private:
    void shiftUp(int k)
    {
        // 使得 k 位置的值与他父节点进行比较，大于则进行交换；k最多与index为1位置进行比较，因此 k=2 or 3时将会是最后一次比较
        while (k > 1 && data[k] > data[k / 2])
        {
            swap(data[k], data[k / 2]);
            k /= 2;
        }
    }

    void shiftDown(int k)
    {
        // 当前最后一个子节点已经交换到了第一个节点，每次比较它的左右叶子节点，那个节点大就和哪个节点交换
        while (2 * k <= count)
        {
            // 因为我们需要考虑到右节点，因此设置j，当右节点大于左节点时转变成右节点的索引
            int j = 2 * k; // 初始为左节点
            if (j+1 <= count && data[j] < data[j + 1])
            {
                j++;
            }
            if (data[k] >= data[j])
            {
                break;
            }

            swap(data[k], data[j]);
            k = j;
        }
    }

    void putNumberInLine(int num, string &line, int index_cur_level, int cur_tree_width, bool isLeft)
    {

        int sub_tree_width = (cur_tree_width - 1) / 2;
        int offset = index_cur_level * (cur_tree_width + 1) + sub_tree_width;
        assert(offset + 1 < line.size());
        if (num >= 10)
        {
            line[offset + 0] = '0' + num / 10;
            line[offset + 1] = '0' + num % 10;
        }
        else
        {
            if (isLeft)
                line[offset + 0] = '0' + num;
            else
                line[offset + 1] = '0' + num;
        }
    }

    void putBranchInLine(string &line, int index_cur_level, int cur_tree_width)
    {

        int sub_tree_width = (cur_tree_width - 1) / 2;
        int sub_sub_tree_width = (sub_tree_width - 1) / 2;
        int offset_left = index_cur_level * (cur_tree_width + 1) + sub_sub_tree_width;
        assert(offset_left + 1 < line.size());
        int offset_right = index_cur_level * (cur_tree_width + 1) + sub_tree_width + 1 + sub_sub_tree_width;
        assert(offset_right < line.size());

        line[offset_left + 1] = '/';
        line[offset_right + 0] = '\\';
    }

public:
    MaxHeap(int capacity)
    {
        data = new Item[capacity + 1];
        count = 0;
        this->capacity = capacity;
    }

    template<typename T>
    MaxHeap(T arr[], int n)
    {
        data = new Item[n + 1];
        this->capacity = n;
        
        for (size_t i = 0; i < n; i++)
        {
            data[i + 1] = arr[i];
        }
        count = n;
        // heap 有一个性质是他最后一个父节点的索引永远是节点数量 / 2
        for (int i = count / 2; i >=1 ; i--)
        {
            // 此处对其所有的父节点进行一次shiftDown   
            shiftDown(i);
        }
    }

    ~MaxHeap()
    {
        delete[] data;
    }

public:
    int size()
    {
        return count;
    }

    bool isEmpty()
    {
        return count == 0;
    }

    // 以树状打印整个堆结构
    void testPrint()
    {
        // 我们的testPrint只能打印100个元素以内的堆的树状信息
        if (size() >= 100)
        {
            cout << "This print function can only work for less than 100 int";
            return;
        }

        // 我们的testPrint只能处理整数信息
        if (typeid(Item) != typeid(int))
        {
            cout << "This print function can only work for int item";
            return;
        }

        cout << "The max heap size is: " << size() << endl;
        cout << "Data in the max heap: ";
        for (int i = 1; i <= size(); i++)
        {
            // 我们的testPrint要求堆中的所有整数在[0, 100)的范围内
            assert(data[i] >= 0 && data[i] < 100);
            cout << data[i] << " ";
        }
        cout << endl;
        cout << endl;

        int n = size();
        int max_level = 0;
        int number_per_level = 1;
        while (n > 0)
        {
            max_level += 1;
            n -= number_per_level;
            number_per_level *= 2;
        }

        int max_level_number = int(pow(2, max_level - 1));
        int cur_tree_max_level_number = max_level_number;
        int index = 1;
        for (int level = 0; level < max_level; level++)
        {
            string line1 = string(max_level_number * 3 - 1, ' ');

            int cur_level_number = min(count - int(pow(2, level)) + 1, int(pow(2, level)));
            bool isLeft = true;
            for (int index_cur_level = 0; index_cur_level < cur_level_number; index++, index_cur_level++)
            {
                putNumberInLine(data[index], line1, index_cur_level, cur_tree_max_level_number * 3 - 1, isLeft);
                isLeft = !isLeft;
            }
            cout << line1 << endl;

            if (level == max_level - 1)
                break;

            string line2 = string(max_level_number * 3 - 1, ' ');
            for (int index_cur_level = 0; index_cur_level < cur_level_number; index_cur_level++)
                putBranchInLine(line2, index_cur_level, cur_tree_max_level_number * 3 - 1);
            cout << line2 << endl;

            cur_tree_max_level_number /= 2;
        }
    }

    void insert(Item item)
    {
        assert(capacity >= count + 1);
        data[++count] = item;
        shiftUp(count); // 将插入数据的位置进行调整
    }

    Item extractMax()
    {
        assert(count > 0);
        swap(data[count], data[1]);
        Item maxData = data[count--];

        shiftDown(1);

        return maxData;
    }
};

#endif // __HEAP_H