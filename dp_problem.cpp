//
// Created by Tomato on 2021/2/18.
//

#include <vector>
#include <algorithm>
using namespace std;

// https://leetcode.com/problems/maximal-square/
class Solution221 {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return 0;
        }
        const int row = matrix.size();
        const int col = matrix[0].size();
        int max_len = 0;
        vector<vector<int>> dp(row+1, vector<int>(col+1, 0));
        for (int i = 1; i <= row; ++i) {
            for (int j = 1; j <= col; ++j) {
                if (matrix[i-1][j-1] != '0') {
                    dp[i][j] = min({dp[i][j-1], dp[i-1][j], dp[i-1][j-1]}) + 1;
                    max_len = max(dp[i][j], max_len);
                }
            }
        }
        return max_len * max_len;
    }
};

//https://leetcode.com/problems/01-matrix/
class Solution542 {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return {};
        }
        const int row = matrix.size();
        const int col = matrix[0].size();
        vector<vector<int>> dp(row+2, vector<int>(col+2, 10001));
        for (int i = 1; i <= row; ++i) {
            for (int j = 1; j <= col; ++j) {
                if (matrix[i-1][j-1] != 0) {
                    dp[i][j] = min({dp[i][j-1], dp[i-1][j]}) + 1;
                } else {
                    dp[i][j] = 0;
                }
            }
        }
        for (int i = row; i >= 1; --i) {
            for (int j = col; j >= 1; --j) {
                if (matrix[i-1][j-1] != 0) {
                    dp[i][j] = min({dp[i+1][j] + 1, dp[i][j+1] + 1, dp[i][j]});
                }
            }
        }
        dp.erase(dp.begin());
        dp.erase(--dp.end());
        for (vector<int> &v : dp) {
            v.erase(v.begin());
            v.erase(--v.end());
        }
        return dp;
    }
};