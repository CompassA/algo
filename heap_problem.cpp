//
// Created by Tomato on 2021/2/18.
//

#include <vector>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/**
 * https://leetcode.com/problems/merge-k-sorted-lists/submissions/
 */
class Solution23 {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) {
            return nullptr;
        }
        const auto& cmp = [](const auto &a, const auto &b) {
            return a->val > b->val;
        };
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> q(cmp);
        for_each(lists.begin(), lists.end(), [&q](const auto &node) {
            if (node != nullptr) {
                q.push(node);
            }
        });
        ListNode h(-1);
        ListNode* head = &h;
        ListNode* tail = head;
        while (!q.empty()) {
            ListNode *cur = q.top();
            q.pop();
            if (cur->next != nullptr) {
                q.push(cur->next);
            }
            tail->next = cur;
            tail = cur;
        }
        ListNode* res = head->next;
        return res;
    }
};