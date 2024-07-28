#include <bits/stdc++.h>
using namespace std;
long long huge = 1e9 + 7;

int answer(int n)
{
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        dp[i][1] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 2; j <= i; j++)
        {
            dp[i][j] = (dp[i - 1][j - 1]) + (dp[i - j][j]);
            dp[i][j] %= huge;
        }
    }
    long total = 0;
    for (int j = 1; j <= n; j++)
    {
        total += dp[n][n];
        total %= huge;
    }
    total %= huge;
    return total;
}
int main()
{
    int n;
    cin >> n;
    int Answer = answer(n);
    cout << Answer;
    return 0;
}