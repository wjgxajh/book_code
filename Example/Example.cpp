/*
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
*/
//#include <iostream>
//#include<algorithm>
//
//using namespace std;
//
//int main()
//{
//    int total_weight = 10;
//    int w[6] = { 0,5,4,3,2,1 };
//    int v[6] = { 0,1,2,3,4,5 };
//    int cot[6] = { 0,1,2,1,2,1 };
//    int dp[11] = { 0 };
//    int path[6][11] = { 0 };
//
//    for (int i = 1; i <= 5; i++)
//        for (int k = 1; k <= cot[i]; k++)
//            for (int j = 10; j >= w[i]; j--)
//                if (dp[j] < dp[j - w[i]] + v[i])
//                {
//                    dp[j] = dp[j - w[i]] + v[i];
//                    path[i][j] = 1;
//                }
//
//    int i = 5, j = 10;
//    while (i > 0 && j > 0)
//    {
//        if (path[i][j] == 1 && cot[i])
//        {
//            cout << i << ' ';
//            j -= w[i];
//            cot[i]--;
//        }
//        else
//            i--;
//    }
//    cout << endl;
//
//    cout << "总的价值为: " << dp[10] << endl;
//    return 0;
//}



/*
题意：10000元，4种面值硬币，给出每种硬币的个数，问最多可以用多少个硬币组合成给定的总价格，输出方案。
思路：就是完全背包需要输出方案，dp[j]表示总价格为j时最多可以有多少个硬币，但是需要维护一下硬币的个数，
实际上在01背包中，我们对所有状态都更新了一次答案，这里我们等于是对4种硬币各跑一次背包，维护一下使用
次数即可。used[j]表示总价格为j时用了多少个某个硬币。pre[j]记录方案，表示j出现更有的答案时是由哪个状态
转移来的。
最后遍历一下输出答案就好了。这里不能滚动数组来做，因为硬币不止1个，滚动只更新了一次答案。
*/

//#include<cstdio>
//#include<cstring>
//#include<iostream>
//#include<vector>
//using namespace std;
//
//const int maxn = 10010;
//const int INF = 0x3f3f3f3f;
//
////int used[maxn];
//int dp[maxn];
//int path[maxn];
//int cnt[4];
//int val[4] = { 1,5,10,25 };
//
//int main()
//{
//    //freopen("int.txt","r",stdin);
//    while (1) {
//        int n, sum = 0;
//        scanf_s("%d", &n);
//        vector<vector<int>>used(4, vector<int>(n + 1, 0));
//        for (int i = 0; i < 4; i++) {
//            scanf_s("%d", &cnt[i]);
//            sum += cnt[i] * val[i];
//        }
//        memset(dp, -INF, sizeof(dp));
//        memset(path, 0, sizeof(path));
//        path[0] = -1;
//        dp[0] = 0;
//        if (!n && !sum)break;
//        for (int i = 0; i < 4; i++) {
//            for (int v = val[i]; v <= n; v++) {
//                cout << "val[i]=" << val[i] << endl;
//                cout << "v-val[i]=" << v - val[i] << endl;
//                if (dp[v - val[i]] + 1 > dp[v] && dp[v - val[i]] >= 0 && used[i][v - val[i]] < cnt[i]) {
//                    dp[v] = dp[v - val[i]] + 1;
//                    used[i][v] = used[i][v - val[i]] + 1;
//                    path[v] = v - val[i];
//                }
//            }
//        }
//        for (int i = 0; i < 4; i++) {
//            for (int j = 0; j <= n; j++) {
//                cout << used[i][j] << " ";
//            }
//            cout << endl;
//        }
//        int ans[100];
//        memset(ans, 0, sizeof(ans));
//        if (dp[n] < 0) {
//            printf("Charlie cannot buy coffee.\n");
//        }
//        else {
//            while (path[n] != -1) {
//                ans[n - path[n]]++;
//                n = path[n];
//            }
//            printf("Throw in %d cents, %d nickels, %d dimes, and %d quarters.\n", ans[val[0]], ans[val[1]], ans[val[2]], ans[val[3]]);
//        }
//    }
//    return 0;
//}

//#include<bits/stdc++.h>
#include<string>
#include<iostream>
using namespace std;

const int v[] = { 1,2,5 };
int num[3], res[9999], tmp[9999];

int main() {
    while (cin >> num[0] >> num[1] >> num[2]) {
        if (!num[0] && !num[1] && !num[2]) break;
        res[0] = 1;
        int last = 0;
        for (int i = 0; i < 3; ++i) {
            memset(tmp, 0, sizeof tmp);
            for (int j = 0; j <= num[i]; ++j)
                for (int k = 0; k <= last; ++k)
                    tmp[k + j * v[i]] += res[k];
            memcpy(res, tmp, sizeof tmp);
            last += num[i] * v[i];
        }
        for (int i = 0; i <= last + 1; ++i) if (!res[i]) {
            printf("%d\n", i);
            break;
        }
    }

    return 0;
}
