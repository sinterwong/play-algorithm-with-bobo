#include <iostream>
#include <assert.h>
using namespace std;
/**
 * @brief 之前的最大堆存在一些问题，一个是当我们的数组类型是一个复杂的数据类型，我们每次进行shiftUp或者shiftDown时进行数据交换将会有非常大的开销，
 * 当然这个问题还是可以通过技术的方式处理掉；而另一个致命的问题是当我们完成了堆排序之后，数据已经乱序，此时就不可以通过index去获取索引了，或者也可
 * 以为我们的数据多加一个index的属性，去记录他的index，但是每次想获取该索引时就需要O(n)级别的复杂度。
 * 为此我们可以设置另一个数组indexes作为我们需要维护的heap，利用原始的数据进行比较，但是更新时只需要更新indexes，这样既处理掉了复杂数据类型交换的
 * 问题，同时不改变原始的数据位置；届时通过index获取数据的复杂度就仅有O(1)了。
 *
 *
 */
template <typename Item>
class IndexMaxHeap
{
public:
    IndexMaxHeap(int capacity)
    {
        data = new Item[capacity + 1];
        indexes = new int[capacity + 1];
        reverses = new int[capacity + 1];

        for (size_t i = 1; i < capacity; i++)
        {
            reverses[i] = 0; // init
        }

        count = 0;
        capacity = capacity;
    }

    ~IndexMaxHeap()
    {
        delete[] data;
        delete[] indexes;
        delete[] reverses;
    }

private:
    Item *data;
    int *indexes;
    int *reverses;
    int capacity;
    int count;

public:
    int size()
    {
        return count;
    }

    bool isEmpty()
    {
        return count == 0;
    }

    void append(Item item)
    {
        assert(capacity >= count + 1);
        int i = count + 1;
        data[i] = item;
        indexes[i] = i;
        reverses[i] = i;
        shiftUp(i);
    }

    Item extractMax()
    {
        assert(count >= 1);
        swap(indexes[1], indexes[count]);
        reverses[indexes[1]] = 1;
        reverses[indexes[count]] = 0;
        Item result = data[indexes[count--]];
        shiftDown(1);
        return result;
    }

    int extractMaxIndex()
    {
        assert(count >= 1);
        int result = indexes[1];
        swap(indexes[1], indexes[count]);
        reverses[indexes[1]] = 1;
        reverses[indexes[count]] = 0;
        count--;
        return result;
    }

    bool contain(int k)
    {
        assert(k + 1 >= 1 && k + 1 <= capacity);
        return reverses[k] != 0;
    }

    Item getItem(int i)
    {
        assert(contain(i));
        return data[i + 1];
    }

    void change(int i, Item item)
    {
        assert(contain(i));
        i += 1;
        data[i] = item;
        // 此时我们并没有对数据在堆中的位置进行索引，因此我们在插入元素之后，想要维护indexes还需要对indexes进行遍历，找到indexes[j] == i，也就是数据在堆中的索引
        // 但是以下的代码遍历的时间复杂度是O(n)，shiftUp和shiftDown都是log(n)，最差的情况下时间复杂度为 n+log(n)也就是O(n)，如果用户在外部进行n次这种操作，最坏
        // 的情况下将退化成O(n^2)级别
        // for (size_t j = 1; j < count; j++)
        // {
        //     if (indexes[j] == i)
        //     {
        //         shiftUp(j);
        //         shiftDown(j);
        //         return;
        //     }
        // }

        // 使用反向查找的思路对如上代码进行优化
        // 获取data[i] 在indexes(堆)中的位置
        int j = reverses[i];
        shiftUp(j);
        shiftDown(j);
    }

private:
    void shiftUp(int k)
    {
        while (k > 1 && data[indexes[k]] > data[indexes[k / 2]])
        {
            swap(indexes[k], indexes[k / 2]);
            // 此时indexes中的元素已经交换，相应的reverses中的元素也应该跟随indexes的值进行更新
            reverses[indexes[k / 2]] = k / 2;
            reverses[indexes[k]] = k;
            k /= 2;
        }
    }

    void shiftDown(int k)
    {
        while (k * 2 <= count)
        {
            int j = k * 2;
            if (j + 1 <= count && data[indexes[j + 1]] > data[indexes[j]])
            {
                j++;
            }
            if (data[indexes[k]] >= data[indexes[j]])
            {
                break;
            }
            swap(indexes[k], indexes[j]);
            reverses[indexes[k]] = k;
            reverses[indexes[j]] = j;
            k = j;
        }
    }
};

int main(int argc, char const *argv[])
{
    return 0;
}
