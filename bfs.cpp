#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <vector>
using namespace std;

/**
 * https://leetcode.com/problems/word-ladder-ii/
 */
class Solution126 {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, const vector<string>& wordList) {
        unordered_set<string> dict;
        for_each(wordList.begin(), wordList.end(), [&dict](const string& str) { dict.insert(str); });
        if (dict.find(endWord) == dict.end()) {
            return vector<vector<string>>();
        }
        unordered_set<string> long_set{ beginWord };
        unordered_set<string> short_set{ endWord };
        dict.erase(beginWord);
        dict.erase(endWord);
        unordered_map<string, vector<string>> next;
        bool changed = false; 
        bool found = false;
        while (!long_set.empty()) {
            unordered_set<string> next_level;
            for (const auto &str : long_set) {
                string str_copy(str);
                for (int i = 0; i < str.size(); ++i) {
                    const char origin = str_copy[i];
                    for (char c = 'a'; c <= 'z'; ++c) {
                        str_copy[i] = c;
                        if (short_set.find(str_copy) != short_set.end()) {
                            changed ? next[str_copy].push_back(str) : next[str].push_back(str_copy);
                            found = true;
                        }
                        if (dict.find(str_copy) != dict.end()) {
                            next_level.insert(str_copy);
                            changed ? next[str_copy].push_back(str) : next[str].push_back(str_copy);
                        }
                    }
                    str_copy[i] = origin;
                }
            }
            if (found) {
                break;
            }
            for_each(next_level.begin(), next_level.end(), [&dict](const string& str) { dict.erase(str); });
            if (next_level.size() >= short_set.size()) {
                long_set = move(next_level);
            } else {
                long_set = move(short_set);
                short_set = move(next_level);
                changed = !changed;
            }
        }
        vector<vector<string>> res;
        vector<string> path;
        dfs(beginWord, endWord, next, res, path);
        return res;
    }

private:
    void dfs(const string& cur, const string& end, unordered_map<string, vector<string>> &next, vector<vector<string>> & res, vector<string> &path) {
        path.push_back(cur);
        if (cur == end) {
            res.push_back(path);
            path.pop_back();
            return;
        }
        for (const string& child : next[cur]) {
            dfs(child, end, next, res, path);
        }
        path.pop_back();
    }
};

int main(int s, char**d) {
    Solution126().findLadders("a", "c", {"a","b","c"});
}
