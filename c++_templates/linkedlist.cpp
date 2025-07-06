#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>
#include <map>
#include <queue>

#define for0(i, n) for (int i = 0; i < (int)(n); ++i)            // 0 based indexing
#define for1(i, n) for (int i = 1; i <= (int)(n); ++i)           // 1 based indexing
#define forc(i, l, r) for (int i = (int)(l); i <= (int)(r); ++i) // closed interver from l to r r inclusive
#define forr0(i, n) for (int i = (int)(n) - 1; i >= 0; --i)      // reverse 0 based.
#define forr1(i, n) for (int i = (int)(n); i >= 1; --i)          // reverse 1 based

#define pb push_back
#define fi first
#define se second

#define present(c, x) ((c).find(x) != (c).end())
#define cpresent(c, x) (find(all(c), x) != (c).end())
#define sz(a) int((a).size())

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef double ld;

class Node
{
public:
    int val;
    Node *next;

    Node(int new_data)
    {
        val = new_data;
        next = nullptr;
    }
};

Node *reverseList(Node *head)
{
    Node *pre = nullptr;
    Node *cur = nullptr;
    while (head != nullptr)
    {
        cur = head->next;
        head->next = pre;
        pre = head;
        head = cur;
    }
    return pre;
}

// merge two sorted lists
// https://leetcode.com/problems/merge-two-sorted-lists/description/

// add two linked lists
// https://leetcode.com/problems/add-two-numbers/description/

// partition-list
// https://leetcode.com/problems/partition-list/description/

int main()
{
    Node *head = new Node(1);
    Node *n1 = new Node(2);
    Node *n2 = new Node(3);
    head->next = n1;
    n1->next = n2;

    Node *res = reverseList(head);

    while (res)
    {
        cout << res->val << " ";
        res = res->next;
    }

    return 0;
}