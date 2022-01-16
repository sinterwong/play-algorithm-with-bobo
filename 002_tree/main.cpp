#include "bst.hpp"
#include "fileOps.hpp"

int main(int argc, char const *argv[])
{
    string filename = "bible.txt";
    vector<string> words;

    if (FileOps::readFile(filename, words))
    {
        // words 加载完毕
        cout << "There are totally " << words.size() << " words in " << filename << endl;
        cout << endl;

        time_t startTime = clock();

        // 统计词频
        BinarySearchTree<string, int> bst = BinarySearchTree<string, int>();

        for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++)
        {
            int *res = bst.search(*iter);
            if (res == nullptr)
            {
                bst.insert(*iter, 1);
            }
            else
            {
                (*res)++;
            }
        }

        // 输出圣经中god一词出现的频率
        if(bst.contain("god"))
            cout << "'god' : " << *bst.search("god") << endl;
        else
            cout << "No word 'god' in " << filename << endl;

        time_t endTime = clock();

        cout << "BST , time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;
        cout << "BST size: " << bst.size() << endl;
        cout << endl;
    }

    return 0;
}
