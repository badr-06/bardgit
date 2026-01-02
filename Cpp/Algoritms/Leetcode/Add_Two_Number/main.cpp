#include <iostream>
#include <list>
#include <vector>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}

};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

        std::list<int> ls;
        int remains = 0;
        while (l1 != nullptr && l2 != nullptr)
        {
            int x = l1->val + l2->val;

            add(ls, x, remains);

            l1 = l1->next;
            l2 = l2->next;
        }
        if(l1 != nullptr){
            while (l1 != nullptr)
            {
                add(ls, l1->val, remains);
            }
            l1 = l1->next;
        }
        else if(l2 != nullptr){
            while (l2 != nullptr)
            {
                add(ls, l2->val, remains);
            }
            l2 = l2->next;
        }
        else if(remains){
            ls.push_front(remains);
        }
        auto it = ls.begin();
        auto end = ls.end();
        ListNode* res = new ListNode(*it);
        ++it;
        for(; it != end; ++it){
            res = new ListNode(*it, res);
        }
        return res;

    }

    void add(std::list<int>& ls, int x, int& remains){
            if(remains) {
                x += remains;
                remains = 0;
            }

            if(x >= 10){
                ls.push_front(x % 10);
                remains = x / 10;
            }
            else {
                ls.push_front(x);
            }
    }
};

int main() {

    // ListNode* l1 = new ListNode(3);
    // l1 = new ListNode(4, l1);
    // l1 = new ListNode(2, l1);


    // ListNode* l2 = new ListNode(4);
    // l2 = new ListNode(6, l2);
    // l2 = new ListNode(5, l2);

    ListNode* l2 = new ListNode(6);
    ListNode* l1 = new ListNode(6);

    Solution s;
    auto res = s.addTwoNumbers(l1, l2);

    return 0;
}

