// Example.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "ch05_1.h"
#include<vector>
#define max(a,b) (((a) > (b)) ? (a) : (b)) 
#define min(a,b) (((a) < (b)) ? (a) : (b)) 
template <typename Type>
void Knapsack(vector<int> &v, vector<int>& w, int c, int n, vector<vector<int>> &m)
{
    //递归初始条件 
    int jMax = min(w[n] - 1, c);
    for (int j = 0; j <= jMax; j++) {
        m[n][j] = 0;
    }

    for (int j = w[n]; j <= c; j++) {
        m[n][j] = v[n];
    }

    //i从2到n-1，分别对j>=wi和0<=j<wi即使m(i,j) 
    for (int i = n - 1; i > 1; i--) {
        jMax = min(w[i] - 1, c);
        for (int j = 0; j <= jMax; j++) {
            m[i][j] = m[i + 1][j];
        }
        for (int j = w[i]; j <= c; j++) {
            m[i][j] = max(m[i + 1][j], m[i + 1][j - w[i]] + v[i]);
        }
    }

    m[1][c] = m[2][c];
    if (c >= w[1]) {
        m[1][c] = max(m[1][c], m[2][c - w[1]] + v[1]);
    }
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[i].size(); j++)
        {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
}

template <typename Type>
void TraceBack(vector<vector<int>>&m, vector<int>& w, int c, int n, vector<int>& x)
{
    for (int i = 1; i < n; i++) {
        if (m[i][c] == m[i + 1][c]) 
            x[i] = 0;
        else {
            x[i] = 1;
            c -= w[i];
        }
    }
    x[n] = (m[n][c]) ? 1 : 0;
}

int main()
{
    int n = 5;
    vector<int> w = { -1, 2, 2, 6, 5, 4 };
    vector<int> v = { -1, 6, 3, 5, 4, 6 };
    int c = 10;

    //int** ppm = new int* [n + 1];
    //for (int i = 0; i < n + 1; i++) {
    //    ppm[i] = new int[c + 1];
    //}
    vector<vector<int>> ppm(n + 1, vector<int>(c + 1, 0));
    vector<int> x = { 0,0,0,0,0,0 };

    Knapsack<int>(v, w, c, n, ppm);
    TraceBack<int>(ppm, w, c, n, x);

    return 0;
    //init();
    //fboard ff;
    //memset(&ff, 0, sizeof(fboard));
    //search(&ff);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
