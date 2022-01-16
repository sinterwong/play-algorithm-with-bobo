#ifndef __BINARY_SEARCH_TREE_SEARCH_FILEOPS_H
#define __BINARY_SEARCH_TREE_SEARCH_FILEOPS_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// 文件相关操作
namespace FileOps
{

    int firstCharacterIndex(const string &s, int start)
    {
        // 从start开始，直到找到了字母为止，返回字母的index即可
        for (size_t i = start; i < s.length(); i++)
        {
            if (isalpha(s[i]))
            {
                // 遇到了一个字符
                return i;
            }
        }
        return s.length();
    }

    string lowerS(const string &s)
    {
        string ret = "";
        for (size_t i = 0; i < s.length(); i++)
        {
            ret += tolower(s[i]);
        }
        return ret;
    }

    // 读取文件名称为filename中的内容，并将其中包含的所有词语放进words中
    bool readFile(const string &filename, vector<string> &words)
    {
        string line; //
        string content = "";

        ifstream file(filename); // file input stream
        if (file.is_open())      // 打开文件，并检查是否打开成功
        {
            while (getline(file, line))
            {
                content += (line + "\n");
            }
            file.close();
        }
        else
        {
            cout << "Can not open " << filename << "!!!" << endl;
            return false;
        }

        // 简易的分词
        int start = firstCharacterIndex(content, 0);
        for (size_t i = start + 1; i <= content.length();)
        {
            if (i == content.length() || !isalpha(content[i]))
            {
                // 如果不是字母的话 或者 i到底的情况下，插入这个词
                words.push_back(lowerS(content.substr(start, i - start)));
                start = firstCharacterIndex(content, i);
                i = start + 1;
            }
            else
            {
                i++;
            }
        }
        return true;
    }
}

#endif //__BINARY_SEARCH_TREE_SEARCH_FILEOPS_H